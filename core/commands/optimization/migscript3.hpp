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
#include <alice/alice.hpp>

#include <mockturtle/mockturtle.hpp>

#include <stdio.h>
#include <fstream>

#include <sys/stat.h>
#include <stdlib.h>

namespace alice
{
ALICE_COMMAND(migscript3, "Optimization", "Exact NPN MIG rewriting")
{
    if (!store<mig_ntk>().empty()) {
        auto &opt = *store<mig_ntk>().current();

        auto start = std::chrono::high_resolution_clock::now();
        mockturtle::depth_view mig_depth{opt};

        //DEPTH REWRITING
        env->out() << "MIG logic depth " << mig_depth.depth() << " Majority nodes " <<
                   opt.num_gates() << std::endl;

        oracle::mig_script3 migopt;
        opt = migopt.run(opt);

        mockturtle::depth_view new_mig_depth{opt};
        env->out() << "MIG logic depth " << new_mig_depth.depth() << " Majority nodes "
                   << opt.num_gates() << std::endl;

        env->out() << "Final ntk size = " << opt.num_gates() << " and depth = " <<
                   new_mig_depth.depth() << "\n";
        env->out() << "Area Delay Product = " << opt.num_gates() * new_mig_depth.depth()
                   << "\n";
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                        (stop - start);
        env->out() << "Full Optimization: " << duration.count() << "ms\n";
        env->out() << "Finished optimization\n";

    } else {
        env->err() << "There is not an MIG network stored.\n";
    }

}
}
