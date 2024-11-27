#!/bin/bash
# ref: https://github.com/bytang/runSuite

PARAMETER_MISMATCH=1
FILE_ERROR=2

# improper command usage error
usage() {
  echo "Usage: runSuite suite-file program" 1>&2
  exit ${PARAMETER_MISMATCH}
}

# unreadable or missing file error
file_error() {
  echo "runSuite: ${1}: no such file or file is unreadable" 1>&2
  exit ${FILE_ERROR}
}

# checks if the file exists and is readable
file_check() {
  head -1 ${1} &> /dev/null
  if [ ${?} -ne 0 ]; then
    file_error ${1}
  fi
}

# checks for proper arguments
if [ ${#} -ne 2 ]; then
  usage
fi

# checks source file
file_check ${1}

# checks program file
file_check ${2}

dir=$(pwd)

for file in $(cat ${1}); do

  in=${dir}/${file}.in
  out=${dir}/${file}.out
  
  file_check ${in}
  file_check ${out}

  output=$(${2} < ${in} 2> /dev/null)
  fail=${?}
  expected=$(cat ${out})

  if [ "${output}" != "${expected}" ]; then
    echo "Test \"${file}\" failed:"
    echo "Input:"
    cat ${in}
    echo "Expected:"
    echo "${expected}"
    echo "Actual:"
    echo "${output}"
  fi
  
  if [ ${fail} -ne 0 ]; then
    echo "Error:"
    ${2} < ${in} > /dev/null
  fi
  
done