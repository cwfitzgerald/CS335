#!/usr/bin/env python3

import re
import os
import argparse

verbose = False

def get_lines(sources):
	for source in sources:
		with open(source, 'r') as file:
			for line in file:
				yield line

include_finder = re.compile(r'^[^\S\r\n]*#\s*include\s*<([^>\r\n]+?)>', re.MULTILINE)

def extract_includes(lines):
	for line in lines:
		match = include_finder.search(line)
		if match:
			if verbose:
				print(match.groups(1)[0])
			yield match.groups(1)[0]

def create_includes(paths):
	for path in paths:
		directive = f"#include <{path}>"
		if verbose:
			print(directive)
		yield directive

def read_old_pch_header(path):
	with open(path, 'r') as f:
		return f.read()

def get_pch_header(directives):
	header = "\n".join(sorted(set(directives))) + '\n'
	if verbose:
		print(header)
	return header

def main():
	global verbose

	parser = argparse.ArgumentParser()
	parser.add_argument('-o', '--output', nargs=1, help='Output header path', type=str)
	parser.add_argument('input', nargs='*', help='Input c/c++ files', type=str)
	parser.add_argument('--verbose', action='store', help='Verbose output')
	parsed = parser.parse_args()

	verbose = parsed.verbose
	infiles = parsed.input
	outfile = parsed.output[0]
	outdir = os.path.dirname(outfile)

	new = get_pch_header(create_includes(extract_includes(get_lines(infiles))))

	if outdir != '':
		os.makedirs(outdir, exist_ok=True)
	if os.path.exists(outfile):
		old = read_old_pch_header(outfile)
		if new == old:
			return

	with open(outfile, 'w') as f:
		f.write(new)

if __name__ == "__main__":
	main()
