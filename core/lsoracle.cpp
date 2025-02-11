/* LSOracle: A learning based Oracle for Logic Synthesis

 * MIT License
 * Copyright 2019 Laboratory for Nano Integrated Systems (LNIS)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#if !defined ALICE_PYTHON
#define ALICE_SETTINGS_WITH_DEFAULT_OPTION true
#endif

/*** Core Libraries ***/
#include <alice/alice.hpp>
#include <mockturtle/mockturtle.hpp>
#include <libkahypar.h>


/*** low priority ***/
//#include <fdeep/fdeep.hpp>
//#include <utah/BiPart.h>

/*** Algorithms ***/
#include "algorithms/partitioning/partition_view.hpp"
#include "utility.hpp"
#include "algorithms/partitioning/hyperg.hpp"
#include "algorithms/partitioning/partition_manager.hpp"
//#include "algorithms/partitioning/cluster.hpp"
//#include "algorithms/partitioning/seed_partitioner.hpp"
//#include "algorithms/partitioning/fpga_seed_partitioner.hpp"
#include "algorithms/partitioning/slack_view.hpp"
#include "algorithms/optimization/rw_script.hpp"
#include "algorithms/optimization/aig_script.hpp"
#include "algorithms/optimization/aig_script2.hpp"
#include "algorithms/optimization/aig_script3.hpp"
#include "algorithms/optimization/aig_script4.hpp"
#include "algorithms/optimization/aig_script5.hpp"
#include "algorithms/optimization/mig_script.hpp"
#include "algorithms/optimization/mig_script2.hpp"
#include "algorithms/optimization/mig_script3.hpp"
#include "algorithms/optimization/test_script.hpp"
#include "algorithms/optimization/optimization.hpp"
#include "algorithms/optimization/optimization_test.hpp"
//#include "algorithms/asic_mapping/techmapping.hpp"
//#include "algorithms/output/mapped_verilog.hpp"

/*** Stores ***/
#include "store/aig.hpp"
#include "store/mig.hpp"
#include "store/xag.hpp"
#include "store/klut.hpp"

/*** Commands ***/
//Input
#include "commands/input/read.hpp"
#include "commands/input/read_aig.hpp"
#include "commands/input/read_blif.hpp"
#include "commands/input/read_verilog.hpp"
#include "commands/input/read_bench.hpp"

//LUT_Map
#include "commands/lut_map/lut_map.hpp"

//Output
#include "commands/output/write_verilog.hpp"
#include "commands/output/write_bench.hpp"
#include "commands/output/write_blif.hpp"
#include "commands/output/write_dot.hpp"
#include "commands/output/write_hypergraph.hpp"
#include "commands/output/show_ntk.hpp"
#include "commands/output/disjoint_clouds.hpp"
//#include "commands/output/get_all_partitions.hpp" //need to add a write_toplevel_verilog method to recover this feature
//#include "commands/output/print_karnaugh_map.hpp" //removed because of frugally deep dependence; will get back to it

//Stats
#include "commands/stats/crit_path_stats.hpp"
#include "commands/stats/depth.hpp"
#include "commands/stats/get_cones.hpp"
#include "commands/stats/ntk_stats.hpp"

//Partitioning
#include "commands/partitioning/partitioning.hpp"
#include "commands/partitioning/partition_detail.hpp"

//Classification
//#include "commands/classification/generate_truth_tables.hpp"

//Optimization
#include "commands/optimization/rwscript.hpp"
#include "commands/optimization/aigscript.hpp"
#include "commands/optimization/migscript.hpp"
#include "commands/optimization/testscript.hpp"
#include "commands/optimization/optimization_command.hpp"
#include "commands/optimization/depthr.hpp"
#include "commands/optimization/cut_e.hpp"
#include "commands/optimization/cut_rewriting.hpp"
#include "commands/optimization/interleaving.hpp"
//#include "commands/optimization/balance.hpp" //seem to be having some shared pointer issues.  Shouldn't be hard, but we never use this alone, so come back to it
#include "commands/optimization/refactor.hpp"
#include "commands/optimization/oracle.hpp"

/* these were commented out in previous master */
// #include "commands/optimization/depth_partition.hpp"
// #include "commands/optimization/depth_based.hpp"
// #include "commands/optimization/mixed_2steps.hpp"

//Asic mapping
//#include "commands/asic_map/asic_map.hpp"

//Testing
/* these were commented out in previous master */
// #include "commands/testing/find_xor.hpp"
// #include "commands/testing/find_part.hpp"
// #include "commands/testing/get_fanout.hpp"
// #include "commands/testing/test_aig_then_part.hpp"
// #include "commands/testing/test_seed_partitioner.hpp"
// #include "commands/testing/test_fpga_seed.hpp"
// #include "commands/testing/pattern_view.hpp"

#include "commands/version.hpp"

#include "kahypar_config.hpp"
#include "config.h"

ALICE_MAIN(lsoracle)
