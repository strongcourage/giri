//===-- sc - SAFECode Compiler Tool ---------------------------------------===//
//
//                     Giri: Dynamic Slicing in LLVM
//
// This file was developed by the LLVM research group and is distributed
// under the University of Illinois Open Source License. See LICENSE.TXT for
// details.
//
//===----------------------------------------------------------------------===//
//
// This program is a tool to run the SAFECode passes on a bytecode input file.
//
//===----------------------------------------------------------------------===//

#include "Giri/TraceFile.h"

#include "llvm/Support/CommandLine.h"

#include <cstdio>
#include <cassert>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("trace file name"), cl::init("-"));

int main(int argc, char ** argv) {
  // Parse the command line options.
  cl::ParseCommandLineOptions(argc, argv, "Print Trace Utility\n");

  // Open the trace file for read-only access.
  int fd = 0;
  if (InputFilename == "-")
    fd = STDIN_FILENO;
  else
    fd = open (InputFilename.c_str(), O_RDONLY);
  assert((fd != -1) && "Cannot open file!\n");

  // Print a header that reminds the user of what the fields mean.
  // printf("-----------------------------------------------------------------------------\n");
  // printf("%10s:  Record Type: %6s: %15s: %16s: %8s\n",
  //        "Index", "ID", "TID", "Address", "Length");
  // printf("-----------------------------------------------------------------------------\n");

  // Read in each entry and print it out.
  Entry entry;
  ssize_t readsize;
  unsigned index = 0;
  printf("-----------------------------------------------------------------------------\n");
  while ((readsize = read(fd, &entry, sizeof(entry))) == sizeof(entry)) {
    // if (entry.type == RecordType::BBType) {
    //   printf("BasicBlock %d - ", entry.id);
    // } else {
    //   break;
    // }
    // printf("%d");
    // printf("%10u: ", index++);

    // Print the entry's type
    switch (entry.type) {
      case RecordType::BBType:
        printf("[BasicBlock]: ");
        break;
    //   case RecordType::LDType:
    //     printf("Load        : ");
    //     break;
    //   case RecordType::STType:
    //     printf("Store       : ");
    //     break;
    //   case RecordType::PDType:
    //     printf("Select      : ");
    //     break;
    //   case RecordType::CLType:
    //     printf("Call        : ");
    //     break;
    //   case RecordType::RTType:
    //     printf("Return      : ");
    //     break;
    //   case RecordType::ENType:
    //     printf("End         : ");
    //     break;
    }

    // Print the value associated with the entry.
    if (entry.type == RecordType::BBType)
      printf("%u\n", entry.id);
    //   printf("%6u: %8lu: %16lx: %8lu\n",
    //          entry.id,
    //          entry.tid,
    //          entry.address,
    //          entry.length);
    // else
    //   printf("%6u: %8lu: %16lx: %8lx\n",
    //          entry.id,
    //          entry.tid,
    //          entry.address,
    //          entry.length);

    // Stop printing entries if we've hit the end of the log.
    if (entry.type == RecordType::ENType) {
      readsize = 0;
      break;
    }
  }
  printf("-----------------------------------------------------------------------------\n");
  if (readsize != 0) {
    fprintf(stderr, "Read of incorrect size\n");
    exit(1);
  }

  return 0;
}
