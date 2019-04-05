project('hw3', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

prog_python = import('python').find_installation('python3')

helpers = [
  'quadratic_probing.h',
  'linear_probing.h',
  'prime.h',
  'double_hashing.h',
  'prime.cc'
]

mains = [
  'create_and_test_hash.cc',
  'spell_check.cc'
]

hw3_pch = custom_target(
  'hw3_pch',
  input: helpers + mains,
  output: 'hw3.hpp',
  command: [prog_python, files('gen_pch.py'), '--output', '@OUTPUT@', '@INPUT@'],
  depend_files: helpers + mains + ['gen_pch.py']
)

r = run_command(prog_python, 'gen_pch.py', '--output', meson.current_build_dir() + '/hw3.hpp', helpers + mains)
if r.returncode() != 0
  error('PCH generation failed.\nstdout:\n' + r.stdout() + '\nstderr:\n' + r.stderr())
endif

executable(
  'create_and_test_hash',
  ['create_and_test_hash.cc'] + helpers, hw3_pch[0],
  install : true,
  cpp_pch : meson.current_build_dir() + '/hw3.hpp',
)

executable(
  'spell_check',
  ['spell_check.cc'] + helpers, hw3_pch[0],
  install : true,
  cpp_pch : meson.current_build_dir() + '/hw3.hpp',
)
