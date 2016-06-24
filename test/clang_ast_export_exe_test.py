# This automated test scripts does the following:
# - Run the clang ast export executable against some input.
# - Record the output to file.
# - Compare the output with an expected results file.

import difflib
import os
import subprocess
import sys
# # raise ValueError(os.getcwd())
# sys.stderr.write(os.getcwd())
# # p = subprocess.Popen(['clang_ast_export_exe/Release/clang_ast_export_exe.exe', 'C:\Users\Johnny\Desktop\clang-test-main.cc | python -m json.tool'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
# p = subprocess.Popen(['clang_ast_export_exe/Release/clang_ast_export_exe.exe', 'C:\Users\Johnny\Desktop\clang-test-main.cc | python -m json.tool'])
# # p = subprocess.Popen(['clang_ast_export_exe/Release/clang_ast_export_exe.exe', 'C:\Users\Johnny\Desktop\clang-test-main.cc'])
# sys.exit(p.wait())
# # sys.exit(0)

import getopt
import sys

def PrintUsage(command):
  print 'Usage:'
  print command + ' --clang_ast_export_exe_file=<executable_to_test.exe> --input_file=<test_input_file.cc> --result_output_file=<generated_output_file.txt> --expected_output_file=<file_with_expected_output.txt>'

def main(argv):
  command = argv[0]
  command_line_arguments = sys.argv[1:]
  executable_file_path = ''
  input_file_path = ''
  result_output_file_path = ''
  output_file_path = ''
  try:
    option_list, args = getopt.getopt(command_line_arguments, "h", ["clang_ast_export_exe_file=", "input_file=", "result_output_file=", "expected_output_file="])
  except getopt.GetoptError:
    PrintUsage(command)
    sys.exit(1)
  for option, argument in option_list:
    if option == '-h':
      PrintUsage(command)
      sys.exit(0)
    elif option == "--clang_ast_export_exe_file":
      executable_file_path = argument
    elif option == "--input_file":
      input_file_path = argument
    elif option == "--result_output_file":
      result_output_file_path = argument
    elif option == "--expected_output_file":
      output_file_path = argument
  # print 'Executable file is "', executable_file_path
  # print 'Input file is "', input_file_path
  # print 'Result file is "', result_output_file_path
  # print 'Output file is "', output_file_path
  formatted_test_output = ''
  test_output = subprocess.check_output([executable_file_path, input_file_path], universal_newlines=True) # + ' | python -m json.tool'])
  open(result_output_file_path, 'w').write(test_output)
  try:
    formatted_test_output, formatting_errors = subprocess.Popen(['python', '-m', 'json.tool'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate(input=test_output)
    formatted_test_output = formatted_test_output.replace('\r', '').strip()
    open(result_output_file_path, 'w').write(formatted_test_output)
  except:
    print sys.exc_info()[0]
    print 'Invalid JSON output:'
    print test_output
    sys.exit(1)
  expected_output = open(output_file_path).read()
  if not (formatted_test_output == expected_output):
    print 'Test result output does not match expectation:'
    # This diff is crappy. Could use FC on windows.
    # for line in (difflib.unified_diff([formatted_test_output], [expected_output])):
      # print line
    sys.exit(1)

if __name__ == "__main__":
   main(sys.argv)