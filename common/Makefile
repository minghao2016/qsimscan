##############################################################################
## This software module is developed by SciDM (Scientific Data Management) in 1998-2015
## 
## This program is free software; you can redistribute, reuse,
## or modify it with no restriction, under the terms of the MIT License.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
## 
## For any questions please contact Denis Kaznadzey at dkaznadzey@yahoo.com
##############################################################################

.PHONY : clean all

CC=$(CCPATH)g++
PIC := $(if $(filter $(shell uname -m),x86_64),-fPIC,)
OPTLEVEL := $(if $(OPTLEVEL),$(OPTLEVEL),-O2)
DEBUGLEVEL := $(if $(DEBUGLEVEL),$(DEBUGLEVEL),-g0)
CPPFLAGS=$(PIC) $(DEBUGLEVEL) $(OPTLEVEL) $(CFL) -D__x86__
AR=ar
ARFLAGS=rc

TARGETNAME=libseq.a
TARGETDIR=../lib
TARGET=$(TARGETDIR)/$(TARGETNAME)

INCLUDE_DIRS=.
INCLUDE_DIRS_SPEC=$(addprefix -I,$(INCLUDE_DIRS))

SYSINCLUDE_DIRS=
SYSINCLUDE_DIRS_SPEC=$(addprefix -I,$(SYSINCLUDE_DIRS))

OBJS = \
common_errors.o \
common_str.o \
fileutils.o \
transitive_closure.o \
misc_utils.o \
platform.o \
rerror.o \
tracer.o \
cmdline.o \
parameters_section.o \
parameters.o \
process_params.o \
cmdline.o \
cmdline_s.o \
sync_control.o \
process_thread.o \
align.o \
align_result.o \
align_result_storage.o \
merging_result_storage.o \
biosequence.o \
blast_results.o \
blast_results_batch.o \
seg_align.o \
sim_merger.o \
fasta.o \
filters.o \
kt_srch_gx.o \
ncbi_weight_matrix.o \
print_batches.o \
scan_results.o \
sequtil.o \
weights.o \
console_util_main.o \
pblast_results.o \
p_kt_scan.o \
gaplib.o \
search_params.o \
ktsearch_params.o \
search_helper_files.o \
acc_str.o






DEPENDENCIES=$(patsubst %.o,%.dep,$(OBJS))

vpath %.h $(INCLUDE_DIRS)
vpath lib% $(LIB_DIRS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDE_DIRS_SPEC) $(SYSINCLUDE_DIRS_SPEC) -c -o $@ $<
	$(CC) $(CPPFLAGS) $(INCLUDE_DIRS_SPEC) $(SYSINCLUDE_DIRS_SPEC) -MM -MG $< >$*.dep

all : $(TARGETDIR) $(TARGET)

$(TARGETDIR) :
	-mkdir $(TARGETDIR)

$(TARGET) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

-include $(DEPENDENCIES)

clean :
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f $(DEPENDENCIES)
