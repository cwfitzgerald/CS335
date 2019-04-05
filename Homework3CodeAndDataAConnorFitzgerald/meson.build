project('hw3', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

helpers = [
  'quadratic_probing.h',
  'linear_probing.h',
  'prime.h',
  'double_hashing.h',
  'prime.cc'
]

hw3_pch = custom_target(
	'hw3_pch',
	input: 'gen_pch.sh',
	output: 'hw3.hpp',
	command: ['bash', '@INPUT@', meson.source_root()]
)

r = run_command('bash', 'gen_pch_meson.sh')
if r.returncode() != 0
  message('FUCK')
else
  message(r.stdout())
  message(r.stderr())
endif

executable(
  'create_and_test_hash',
  ['create_and_test_hash.cc'] + helpers, hw3_pch[0],
  install : true,
  cpp_pch : meson.build_root() + '/hw3.hpp',
)



executable(
  'spell_check',
  ['spell_check.cc'] + helpers,
  install : true,
)
