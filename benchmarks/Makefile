# LSOracle: A learning based Oracle for Logic Synthesis
# MIT License
# Copyright 2019 Laboratory for Nano Integrated Systems (LNIS)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

CLK_PERIOD := 10
STA := sta
LSORACLE := lsoracle
LSORACLE_PLUGIN := oracle
ABC := yosys-abc
YOSYS := yosys
YOSYS_PLUGIN := oracle
TEE := cat - >
ISCAS85 := iscas85/c432.v iscas85/c880a.v iscas85/c3540a.v iscas85/c5288.v iscas85/c2670a.v iscas85/c5315a.v iscas85/c3540.v iscas85/c1908a.v iscas85/c7552.v iscas85/c499.v iscas85/c2670.v iscas85/c1908.v iscas85/c5315.v iscas85/c1335.v
ISCAS89 := iscas89/s1196.v iscas89/s1238.v iscas89/s15850.v
OPDB := opdb/chip_bridge.pickle.v opdb/fpu.pickle.v opdb/gng.pickle.v # opdb/sparc_core.pickle.v
EPFL := EPFL/adder.v EPFL/arbiter.v EPFL/bar.v EPFL/i2c.v EPFL/log2.v EPFL/max.v EPFL/mem_ctrl.v EPFL/multiplier.v #EPFL/sin.v EPFL/sqrt.v EPFL/square.v EPFL/voter.v
ORIGINAL_FILES := picorv32/picorv32.v ibex/ibex.v ${OPDB} ${EPFL} # ${ISCAS85} ${ISCAS89}

################################################################
######################## Targets ###############################
################################################################

AIG_FILES := $(patsubst %.v,%.aig,${ORIGINAL_FILES})
AIG_LOGS := $(patsubst %.v,%.aig.log,${ORIGINAL_FILES})

SDC_SCRIPTS := $(patsubst %.v,%_lsoracle.sdc,${ORIGINAL_FILES}) $(patsubst %.v,%_abc.sdc,${ORIGINAL_FILES}) $(patsubst %.v,%_unoptimized.sdc,${ORIGINAL_FILES}) $(patsubst %.v,%_aigscript.sdc,${ORIGINAL_FILES}) $(patsubst %.v,%_migscript.sdc,${ORIGINAL_FILES})

SYNTH_BASE := $(patsubst %.v,%.rtl,${ORIGINAL_FILES})
SYNTH_BASE_LOGS := $(patsubst %.rtl,%.synth.log,${SYNTH_BASE})

LSORACLE_OUTPUTS := $(patsubst %.rtl,%_lsoracle.rtl,${SYNTH_BASE})
LSORACLE_SYNTH_LOG := $(patsubst %.rtl,%_lsoracle.synth.log,${SYNTH_BASE})
LSORACLE_TECHMAP_OUTPUTS := $(patsubst %.rtl,%_lsoracle.mapped.v,${SYNTH_BASE})
LSORACLE_SYNTH_REPORTS := $(patsubst %.rtl,%_lsoracle.synth_report,${SYNTH_BASE})
LSORACLE_TECHMAP_LOGS := $(patsubst %.rtl,%_lsoracle.tech.log,${SYNTH_BASE})
LSORACLE_TIMING_REPORT := $(patsubst %.rtl,%_lsoracle.timing,${SYNTH_BASE})
LSORACLE_TIMING_LOG := $(patsubst %.rtl,%_lsoracle.sta.log,${SYNTH_BASE})

AIGSCRIPT_OUTPUTS := $(patsubst %.rtl,%_aigscript.rtl,${SYNTH_BASE})
MIGSCRIPT_OUTPUTS := $(patsubst %.rtl,%_migscript.rtl,${SYNTH_BASE})

ABC_OUTPUTS := $(patsubst %.rtl,%_abc.rtl,${SYNTH_BASE})
UNOPT_OUTPUTS := $(patsubst %.rtl,%_unoptimized.rtl,${SYNTH_BASE})
SYNTH_OUTPUTS := ${LSORACLE_OUTPUTS} ${UNOPT_OUTPUTS} ${ABC_OUTPUTS} ${AIGSCRIPT_OUTPUTS} ${MIGSCRIPT_OUTPUTS}
SYNTH_LOGS := $(patsubst %.rtl,%.synth.log,${SYNTH_OUTPUTS})

SYNTH_REPORTS := $(patsubst %.synth.log,%.synth_report,${SYNTH_LOGS})
TECHMAP_OUTPUTS := $(patsubst %.rtl,%.mapped.v,${SYNTH_OUTPUTS})
TECHMAP_LOGS := $(patsubst %.rtl,%.tech.log,${SYNTH_OUTPUTS})
TIMING := $(patsubst %.mapped.v,%.sta.log,${TECHMAP_OUTPUTS})
TIMING_REPORTS := $(patsubst %.sta.log,%.timing,${TIMING})
#EVERYTHING_REPORTS := $(patsubst %.v,%.everything,${ORIGINAL_FILES})
REPORTS := $(patsubst %.v,%.report,${ORIGINAL_FILES})
################################################################
######################## Phony targets #########################
################################################################
all: everything.png

.PHONY: extract synth reports techmap reports timing everything_reports clean all reset

.PRECIOUS: ${SDC_SCRIPTS} ${AIG_FILES} ${AIG_LOGS} ${SYNTH_BASE} ${SYNTH_BASE_LOGS} ${SYNTH_OUTPUTS} ${SYNTH_LOGS} ${REPORTS} ${TECHMAP_OUTPUTS} ${TECHMAP_LOGS} ${TIMING} ${SYNTH_REPORTS} ${TIMING_REPORTS} ${EVERYTHING_REPORTS} ${REPORTS}

.DELETE_ON_ERROR:

extract: ${SYNTH_BASE}

synth: $(SYNTH_OUTPUTS)

techmap: $(TECHMAP_OUTPUTS)

reports: ${REPORTS}

timing: ${TIMING}

sdc_skel: $(patsubst %.v,%.sdc,$(wildcard iscas89/*.v))

reset:
	rm -f ${LSORACLE_OUTPUTS} ${LSORACLE_SYNTH_LOG} ${LSORACLE_TECHMAP_OUTPUTS} ${LSORACLE_SYNTH_REPORTS} ${LSORACLE_TECHMAP_LOGS} ${LSORACLE_TIMING_REPORT} ${LSORACLE_TIMING_LOG} ${REPORTS}

clean: clean_reports
	rm -f ${AIG_FILES} ${AIG_LOGS} ${SYNTH_BASE} ${SYNTH_BASE_LOGS} ${SYNTH_OUTPUTS} ${SYNTH_LOGS} ${TECHMAP_OUTPUTS} ${TIMING} ${SDC_SCRIPTS} ${TECHMAP_LOGS}

clean_reports:
	rm -f ${SYNTH_REPORTS} ${TIMING_REPORTS} ${REPORTS} ${EVERYTHING_REPORTS}  everything.tsv everything.png
################################################################
######################### SYNTHESIS ############################
################################################################

%.rtl %.synth.log &: %.v
	${YOSYS} -Q -p "read_verilog -sv $<; synth -auto-top -flatten -noabc; rename -top top; write_rtlil $*.rtl; stat" | ${TEE} $*.synth.log

# This works in limited circumstances due to flip-flops
%.aig %.aig.log &: %.rtl
	${YOSYS} -Q -p "read_rtlil $<; dffunmap; aigmap; write_aiger $*.aig" | ${TEE} $*.aig.log


%_lsoracle.rtl %_lsoracle.synth.log %_lsoracle.parts %_lsoracle.fixed &: %.rtl
	$(eval TEMP=$(shell mktemp))
	echo "ps -a; partitioning -i $*_lsoracle.fixed -o $*_lsoracle.parts; optimization ; ps -m; crit_path_stats; ntk_stats " > ${TEMP}
	${YOSYS} -m ${YOSYS_PLUGIN} -Q -p "read_rtlil $<; lsoracle -lso_exe ${LSORACLE} -script ${TEMP}; techmap; opt -purge; stat; write_rtlil $*_lsoracle.rtl" | ${TEE} $*_lsoracle.synth.log
	rm ${TEMP}

%_aigscript.rtl %_aigscript.synth.log &: %.rtl
	${YOSYS} -m ${YOSYS_PLUGIN} -Q -p "read_rtlil $<; lsoracle -lso_exe ${LSORACLE} -aig; techmap; opt -purge; stat; write_rtlil $*_aigscript.rtl" | ${TEE} $*_aigscript.synth.log

%_migscript.rtl %_migscript.synth.log &: %.rtl
	${YOSYS} -m ${YOSYS_PLUGIN} -Q -p "read_rtlil $<; lsoracle -lso_exe ${LSORACLE} -mig; techmap; opt -purge; stat; write_rtlil $*_migscript.rtl" | ${TEE} $*_migscript.synth.log

%_unoptimized.rtl: %.rtl
	cp $< $@

%.hpg: %.rtl
	$(eval TEMP=$(shell mktemp))
	echo "write_hypergraph $@" > ${TEMP}
	${YOSYS} -m ${YOSYS_PLUGIN} -Q -p "read_rtlil $<; lsoracle -lso_exe ${LSORACLE} -script ${TEMP}"
	rm ${TEMP}

%_abc.rtl %_abc.synth.log &: %.rtl
	${YOSYS} -Q -p "read_rtlil $<; abc -script techmapping/resyn2rs.abc; techmap; stat; write_rtlil $*_abc.rtl" | ${TEE} $*_abc.synth.log

%.tech_equiv.log: %_lsoracle.mapped.v %_unoptimized.mapped.v
	${YOSYS} -p "read_verilog ${word 2,$^}; rename -top gold; design -stash gold;\
		read_verilog $<; rename -top gate; design -stash gate; \
		design -copy-from gold -as gold gold; design -copy-from gate -as gate gate; \
		equiv_make -inames gold gate equiv; hierarchy -top equiv; equiv_simple; equiv_status -assert" | ${TEE} $@
%.equiv.log: %_lsoracle.rtl %.rtl
	${YOSYS} -p "read_rtlil ${word 2,$^}; rename -top gold; design -stash gold;\
		read_rtlil $<; rename -top gate; design -stash gate; \
		design -copy-from gold -as gold gold; design -copy-from gate -as gate gate; \
		equiv_make -inames gold gate equiv; hierarchy -top equiv; equiv_simple; equiv_status -assert" | ${TEE} $@

%.mapped.v %.tech.log &: %.rtl
	CIRCUIT_INPUT=$* ${YOSYS} -Q -c techmapping/synth.tcl | ${TEE} $*.tech.log

################################################################
########################### TIMING #############################
################################################################

# this is there to help generate these, but they need to be tweaked to get clocks.
%.sdc_skel: %.rtl
	echo "create_clock -name clk -period ${CLK_PERIOD} {clk_i}" > $@
	echo "set_input_delay -clock clk 0 {" >> $@
	${YOSYS} -Q -p  'read_rtlil $<; select i:* -list' | sed -e '/^top/!d' -e 's/top\///' >> $@
	echo "}" >> $@
	echo "set_output_delay -clock clk 0 {" >> $@
	${YOSYS} -Q -p  'read_rtlil $<; select o:* -list' | sed -e '/^top/!d' -e 's/top\///' >> $@
	echo "}" >> $@

%_lsoracle.sdc: %.sdc
	cp $< $@
%_unoptimized.sdc: %.sdc
	cp $< $@
%_migscript.sdc: %.sdc
	cp $< $@
%_aigscript.sdc: %.sdc
	cp $< $@
%_abc.sdc: %.sdc
	cp $< $@

# %_lsoracle.sdc %_abc.sdc %_migscript.sdc %_aigscript.sdc %_unoptimized.sdc: %.sdc
# 	cp $< $@

%.sta.log: %.mapped.v %.sdc
	VERILOG_INPUT=$< VERILOG_TOP=top SDC_FILE=$*.sdc ${STA} -exit techmapping/sta.tcl | ${TEE} $@

################################################################
######################### REPORTS ##############################
################################################################
# Dummy columns if previous doesn't exist.
previous:
	mkdir -p previous

previous/%_lsoracle.everything: | previous
	@ echo -n "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" > $@

%.timing: %.sta.log %.tech.log
	$(eval TYPE=$(shell echo $* | sed 's/^.*_\([a-z]*\)$$/\1/'))
	@ echo generating report $@
	@ sed -n 's/^Combinational\s*\([-.e0-9]*\)\s*\([-.e0-9]*\)\s*\([-.e0-9]*\)\s*\([-.e0-9]*\)\s*\([.0-9]*\)%.*/${TYPE}_internal_power\t\1\n${TYPE}_switching_power\t\2\n${TYPE}_leakage_power\t\3\n${TYPE}_total_power\t\4\n${TYPE}_percent_power\t\5/p' $< > $@
	@ sed -n 's/\s*-\([0-9.]*\)\s *data arrival time/\1/p' $< | python3 -c 'import sys; print("${TYPE}_arrival\t", max([float(i) for i in sys.stdin.readlines()]))' >> $@
	@ sed -n 's/worst slack \([0-9.]*\)/${TYPE}_worst_slack\t\1/p' $< >> $@
	@ sed -e "/Area/!d" -e "s/.*Area = *\([0-9.]*\) .*/${TYPE}_area\t\1/" $*.tech.log >> $@

%_lsoracle.synth_report: %_lsoracle.synth.log
	@ echo generating report $@
	@ sed -n -e "s/LSOracle: inputs: \([0-9]*\)/inputs\t\1/p" \
	-e "s/LSOracle: outputs: \([0-9]*\)/outputs\t\1/p" \
	-e "s/LSOracle: AIG level: \([0-9]*\)/unoptimized_level\t\1/p" \
	-e "s/LSOracle: AIG nodes: \([0-9]*\)/unoptimized_nodes\t\1/p" \
	-e "s/LSOracle.* Using \([0-9]*\) partitions/lsoracle_partitions\t\1/p" \
	-e "s/LSOracle: Final ntk size = \([0-9]*\) and depth = \([0-9]*\)/lsoracle_nodes\t\1\nlsoracle_level\t\2/p" \
	-e "s/LSOracle: \([0-9]*\) AIGs and \([0-9]*\) MIGs/lsoracle_aigs\t\1\\nlsoracle_migs\t\2/p" \
	-e "s/LSOracle: Full Optimization: \([0-9]*\)ms/lsoracle_runtime\t\1/p" \
	-e "s/LSOracle: MAJ nodes internally = \([0-9]*\)/lsoracle_maj_nodes_internal\t\1/p" \
	-e "s/LSOracle: AND nodes internally = \([0-9]*\)/lsoracle_and_nodes_internal\t\1/p" \
	-e "s/LSOracle: AND nodes on critical path = \([0-9]*\)/lsoracle_critical_and\t\1/p" \
	-e "s/LSOracle: MAJ nodes on critical path = \([0-9]*\)/lsoracle_critical_maj\t\1/p" \
	-e "s/LSOracle: INPUTS nodes on critical path = \([0-9]*\)/lsoracle_critical_inputs\t\1/p" < $< > $@

%_migscript.synth_report: %_migscript.synth.log
	@ echo generating report $@
	@ sed -n -e "s/LSOracle: Final ntk size = \([0-9]*\) and depth = \([0-9]*\)/migscript_nodes\t\1\\nmigscript_level\t\2/p" \
	-e "s/LSOracle: Full Optimization: \([0-9]*\)ms/migscript_runtime\t\1/p" \
	-e "s/LSOracle: MAJ nodes internally = \([0-9]*\)/migscript_maj_nodes_internal\t\1/p" \
	-e "s/LSOracle: AND nodes internally = \([0-9]*\)/migscript_and_nodes_internal\t\1/p" \
	-e "s/LSOracle: AND nodes on critical path = \([0-9]*\)/migscript_critical_and\t\1/p" \
	-e "s/LSOracle: MAJ nodes on critical path = \([0-9]*\)/migscript_critical_maj\t\1/p" \
	-e "s/LSOracle: INPUTS nodes on critical path = \([0-9]*\)/migscript_critical_inputs\t\1/p" < $< > $@

%_aigscript.synth_report: %_aigscript.synth.log
	@ sed -n -e "s/LSOracle: Final ntk size = \([0-9]*\) and depth = \([0-9]*\)/aigscript_nodes\t\1\\naigscript_level\t\2/p" \
	-e "s/LSOracle: Full Optimization: \([0-9]*\)ms/aigscript_runtime\t\1/p" < $< > $@

%_abc.synth_report: %_abc.synth.log
	@ echo generating report $@
	@ sed -n 's/ABC:.*and = *\([0-9]*\) *lev = *\([0-9*]\)/abc_nodes\t\1\nabc_level\t\2/p' < $< > $@

%.report: %_lsoracle.synth_report %_lsoracle.timing %_abc.synth_report %_abc.timing %_unoptimized.timing %_migscript.synth_report %_migscript.timing %_aigscript.synth_report %_aigscript.timing
	@ echo "circuit\t$*" > $@
	cat $^ >> $@

#%.everything: %.report
#	@ echo generating report $@
#	@ cut -f1 < $< | tr '\n' '\t' | sed 's/\t$$//' > $@
#	@ echo >> $@
#	@ cut -f2 < $< | tr '\n' '\t' | sed 's/\t$$//' >> $@
#	@ echo >> $@
everything.tsv: ${REPORTS}
	@ echo generating report $@
	python3 combine_report.py $^

#everything.tsv: ${EVERYTHING_REPORTS}
#	@ echo generating report $@
#	python3 combine_report.py $< $^

everything.png everything.pdf: everything.tsv
	python3 plot_bars.py everything.tsv previous/everything.tsv $@
