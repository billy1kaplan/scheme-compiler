#!/usr/bin/python

import sys
import re

def compile_leak_block(text):
    return re.compile(f'{text}:\s+(?P<n>\d+)\s+bytes')

def error_block():
    return re.compile('ERROR SUMMARY: (?P<n>\d+) errors')

def extract_n(match):
    if match:
        return int(match.group('n'))
    else:
        return 0

def main():
    definitely = compile_leak_block('definitely lost')
    indirectly = compile_leak_block('indirectly lost')
    possibly = compile_leak_block('possibly lost')
    reachable = compile_leak_block('still reachable')
    error = error_block()

    tests = [definitely, indirectly, possibly, reachable, error]

    lines = sys.stdin.readlines()
    text = '\n'.join(lines)

    issues = list(map(lambda test: extract_n(re.search(test, text)), tests))

    if any(issues):
        print(text)
    else:
        print('Leak Test Passed')

if __name__ == '__main__':
    main()
