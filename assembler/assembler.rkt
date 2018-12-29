#lang racket
; Utility
(define (flatmap f list)
  (apply append (map f list)))

(define sample-input
'((assign proc (op make-compiled-procedure) (label entry1))
  (goto (label after-lambda2))
  entry1
  (assign env (op compiled-procedure-env) (reg proc))
  (assign env (op extend-environment) (const (n)) (reg arg1) (reg env))
  (assign val (const 1))
  (assign arg1 (op list) (reg val))
  (assign val (op lookup-variable-value) (const n) (reg env))
  (assign arg1 (op cons) (reg val) (reg arg1))
  (assign val (op +) (reg arg1))
  (jump-entry (reg continue))
  after-lambda2
  (assign val (const 1))
  (assign arg1 (op list) (reg val))
  compiled-branch4
  (assign-continue (label after-call5))
  (assign tmp (op compiled-procedure-entry) (reg proc))
  (jump-entry (reg tmp))
  after-call5
  ))
  
(define (remove-labels source)
  ;; Returns an association list of labels to line numbers
  (define (enumerate line labels source)
    (cond ((null? source) labels)
          ;; Label found
          ((not (pair? (car source)))
           (enumerate line (cons (cons (car source) line) labels) (cdr source)))
          (else
           (enumerate (+ line 1) labels (cdr source)))))
  ;; Handles removing labels                                                                               
  (define (replace-labels source)
    (let ((labels (enumerate 0 '() source)))
      (define (replace-label line)
        (cond ((null? line) '())
              ;; Assume there's no further nesting in a properly constructed label
              ((and (pair? line) (eq? (car line) 'label))
               (cdr (assoc (cadr line) labels)))
              ((pair? line) (cons (replace-label (car line))
                                  (replace-label (cdr line))))
              (else line)))
      (define (handle-line line text)
        (if (not (pair? line))
            text
            (cons (replace-label line)
                  text)))
      (foldr handle-line '() source)))
  (replace-labels source))

(define (tagged-union value tag)
  (and (pair? value) (eq? tag (car value))))

(define (assign? exp)
  (tagged-union exp 'assign))

(define (env? exp)
  (tagged-union exp 'assign-env))

(define (goto? exp)
  (tagged-union exp 'goto))

(define (continue? exp)
  (tagged-union exp 'assign-continue))

(define (label? exp)
  (and (not (null? exp))
       (not (pair? exp))))

(define (jump? exp)
  (tagged-union exp 'jump-entry))

(define implicit-env
  '(EXTND LOOKUP))

;; Transformers
(define builtins
  '((+ ADD)
    (- MINUS)
    (/ DIV)
    (* MUL)
    (list LIST)
    (cons CONS)
    (car CAR)
    (cdr CDR)
    (lookup-variable-value LOOKUP)
    (extend-environment EXTND)
    (make-compiled-procedure MKPROC)
    (compiled-procedure-entry COMPILED_PROC_ENTRY)
    (compiled-procedure-env COMPILED_PROCEDURE_ENV)
    ))

(define (symbol->upper sym)
  (define (to-upper ch)
    (let ((char-code (char->integer ch)))
      (let ((is-lower (and (>= char-code (char->integer #\a))
                           (<= char-code (char->integer #\z)))))
        (if is-lower
            (integer->char (+ char-code (- (char->integer #\a)) (char->integer #\A)))
            ch))))
  (string->symbol (list->string (map to-upper (string->list (symbol->string sym))))))

(symbol->upper 'val)

(define (fix-register inst)
  (if (tagged-union inst 'reg)
      (let ((register (if (eq? (cadr inst) 'arg1)
                          'argl
                          (cadr inst))))
        (string->symbol (string-append (symbol->string (symbol->upper register)) "_REG")))
      inst))

(define (translate-assign exp)
  (let ((reg (cadr exp))
        (op (caaddr exp))
        (op-body (car (cdaddr exp)))
        (body (cdddr exp)))
    (define (translate-op)
      (let ((primitive (cadr (assoc op-body builtins))))
        (if (memq primitive implicit-env)
            (list (filter (lambda (x) (not (eq? 'ENV x)))
                          `(,primitive ,(fix-register (list 'reg reg)) ,@(map fix-register body))))
            `((,primitive ,(fix-register (list 'reg reg)) ,@(map fix-register body))))))
    (define (translate-const) `((LOAD ,(fix-register (list 'reg reg)) ,op-body)))
    (if (eq? op 'const)
        (translate-const)
        (translate-op))))

(define (translate-goto instruction)
  `((GOTO ,(cadr instruction))))

(define (translate-continue instruction)
  `((ASSIGN_CONTINUE ,(cadr instruction))))

(define (translate-jump instruction)
  `((JUMP ,(fix-register (cadr instruction)))))

(define assign-exp '((assign val (op list) (reg argl))))
;(define assign-exp '(assign proc (const 1)))

;; Intruction -> list of Machine level
(define (translate instruction)
  (cond ((assign? instruction) (translate-assign instruction))
        ((goto? instruction) (translate-goto instruction))
        ((jump? instruction) (translate-jump instruction))
        ((continue? instruction) (translate-continue instruction))
        (else (list instruction))))

(define (to-string el)
  (cond ((symbol? el) (symbol->string el))
        ((fixnum? el) (number->string el))
        ((flonum? el) (number->string el))
        ((string? el) el)
        ((boolean? el) (if el "true" "false"))
        ((null? el) "")
        ((pair? el) (string-append "(" (to-string (car el)) ", " (to-string (cdr el)) ")"))
        (else (error "Can't convert: " el "to string"))))

(define (to-value el)
  (cond ((symbol? el) (string-append "SYMBOL_VALUE(\"" (to-string el) "\")"))
        ((fixnum? el) (string-append "INT_VALUE(" (to-string el) ")"))
        ((flonum? el) (string-append "DOUBLE_VALUE(" (to-string el) ")"))
        ((string? el) (string-append "STRING_VALUE(\"" (to-string el) "\")"))
        ((boolean? el) (string-append "BOOL_VALUE(" (if el "true" "false") ")"))
        ((null? el) "NIL_VALUE")
        ((pair? el) (string-append "cons(" (to-value (car el)) ", " (to-value (cdr el)) ")"))
        (else (error "Can't convert: " el "to string"))))

(define (load-op index sym)
  (cons 'INPUT
        (cons index sym)))

(define (extract-constants instructions)
  (define (find-const instruction)
    (if (pair? instruction)
        (filter (lambda (part) (tagged-union part 'const)) instruction)
        '()))
  (define (iter constants index acc instructions)
    (if (null? instructions)
        (cons (reverse (cons '(END_INPUT) constants)) (reverse (cons '(END) acc)))
        (let ((const-term (find-const (car instructions))))
          (if (not (null? const-term))
              (iter (cons (load-op index (cadr (car const-term))) constants)
                    (+ index 1)
                    (cons (map (lambda (part)
                                 (if (equal? part (car const-term))
                                     'TMP
                                     part)) (car instructions))
                          (cons `(LOAD TMP ,index)
                                acc))
                    (cdr instructions))
              (iter constants index (cons (car instructions) acc) (cdr instructions))))))
  (iter '() 0 '() instructions))

(define (format instructions)
  (define (handle instruction)
    (string-append " { " (foldr (lambda (cur acc)
                            (string-append (to-string cur) ", " acc))
                          ""
           instruction) " }, "))
    (map handle instructions))

(define (to-machine instructions)
  (let ((byte-code 
         (extract-constants
          (flatmap translate instructions))))
    (cons (car byte-code)
          (remove-labels (cdr byte-code)))))

;(define out (open-output-file "/home/billy/Projects/scheme-compiler/assembler/bytecode.cscm"))
;(write "static Operation arr[100] = { " out)
;(for-each (lambda (line) (write line out)) (to-machine sample-input))
;(close-output-port out)
(define (println instruction)
  (let ((inner (if (tagged-union instruction 'END_INPUT)
                   "END_INPUT, "
                   (string-append (symbol->string (car instruction))
                                  ", "
                                  (number->string (cadr instruction))
                                  ", "
                                  (to-value (cddr instruction))))))
        (string-append "{ " inner " },")))

(define (print-inst instruction)
  (string-append "{ "
                 (apply string-append (map (lambda (inst)
                                             (string-append (to-string inst) ", "))
                                           instruction))
                 " },"))


(define sample-load
  `(,(load-op 0 1)
    ,(load-op 1 1.1)
    ,(load-op 2 "HELLO WORLD!")
    ,(load-op 3 'n)
    ,(load-op 4 '(n))
    ,(load-op 5 #t)
    (END_INPUT)))

(let ((instructions (to-machine sample-input)))
  ;(define out (open-output-file "/home/billy/Projects/scheme-compiler/assembler/load.vm"))
  (define out (current-output-port))
  (display (string-append "LoadInstruction load[" (number->string (length (car instructions))) "] = {") out)
  (newline out)
  (for-each (lambda (line)
              (display (println line) out)
              (newline out))
            (car instructions))
  (display "};" out)
  (newline out)
  (newline out)
  (display (string-append "static Operation ops[" (number->string (length (cdr instructions))) "] = {") out)
  (newline out)
  (for-each (lambda (line)
              (display (print-inst line) out)
              (newline out))
            (cdr instructions))
  (display "};")
  )