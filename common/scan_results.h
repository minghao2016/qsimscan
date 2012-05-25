
//////////////////////////////////////////////////////////////////////////////
// This software module is developed by SCIDM team in 1999-2008.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
// For any questions please contact SciDM team by email at team@scidm.org
//////////////////////////////////////////////////////////////////////////////

#ifndef __scan_results_h__
#define __scan_results_h__
#pragma warning (disable:4786)
#include <map>
#include <platform.h>
#include <pqueue.h>
#include "result_reciever.h"
#include "biosequence.h"
#include "align_result_storage.h"
#include "weights.h"

enum SEQ_SCAN_TYPE
{
    SST_NN,
    SST_NN_REV,
    SST_AA,
    SST_AA_REV,
    SST_AN,
    SST_NA,
    SST_NA_REV
};


struct BATCH;
class ALIGN;
class ScanResults : public ResultReciever, public AlignResultStorage
{
public:
    ScanResults (ALIGN* align, int keep_per_query, SEQ_SCAN_TYPE scantype, WEIGHTS<int, 24>* wm, double score_thresh = 0, int rep_len = 0, double rep_perc = 0);
    virtual ~ScanResults ();

    virtual void match_found (SEQ* query_seq,  SEQ* search_seq, int score);

    int totalFound    () {return _total_found;   }
    int passedRepeats () {return _passed_repeats;}

private:

    void process_match_nn (NN_SEQ* query_seq, NN_SEQ* search_seq, int score);
    void process_match_aa (AA_SEQ* query_seq, AA_SEQ* search_seq, int score);
    void process_match_an (AA_SEQ* query_seq, NA_SEQ* search_seq, int score);
    void process_match_na (NA_SEQ* query_seq, AA_SEQ* search_seq, int score);
    void process_match_na_rev (AA_SEQ* search_seq, NA_SEQ* query_seq, int score);

    SEQ_SCAN_TYPE _scan_type;

    // filters
    ALIGN* _aligner;
    #define MAX_BATCHES 200
    BATCH _batches [MAX_BATCHES];

    WEIGHTS<int, 24>* _wm;

    int  _score_thresh;
    int  _rep_percent;
    int  _rep_len;
    int* _rep_buf;

    longlong _cur_id;

    int _total_found;
    int _passed_repeats;
};



#endif
