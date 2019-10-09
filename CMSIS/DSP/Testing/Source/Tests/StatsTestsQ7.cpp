#include "arm_math.h"
#include "StatsTestsQ7.h"
#include "Error.h"
#include "Test.h"

//#include <cstdio>

#define SNR_THRESHOLD 20
/* 

Reference patterns are generated with
a double precision computation.

*/
#define ABS_ERROR_Q7 ((q7_t)20)
#define ABS_ERROR_Q31 ((q31_t)(1<<15))


    void StatsTestsQ7::test_max_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;
        uint32_t  indexval;

        q7_t *refp  = ref.ptr();
        int16_t  *refind = maxIndexes.ptr();

        q7_t *outp  = output.ptr();
        int16_t  *ind    = index.ptr();

        arm_max_q7(inp,
              inputA.nbSamples(),
              &result,
              &indexval);

        outp[0] = result;
        ind[0] = indexval;

        ASSERT_EQ(result,refp[this->refOffset]);
        ASSERT_EQ((int16_t)indexval,refind[this->refOffset]);

    }

    void StatsTestsQ7::test_min_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;
        uint32_t  indexval;

        q7_t *refp  = ref.ptr();
        int16_t  *refind = minIndexes.ptr();

        q7_t *outp  = output.ptr();
        int16_t  *ind    = index.ptr();

        arm_min_q7(inp,
              inputA.nbSamples(),
              &result,
              &indexval);

        outp[0] = result;
        ind[0] = indexval;

        ASSERT_EQ(result,refp[this->refOffset]);
        ASSERT_EQ((int16_t)indexval,refind[this->refOffset]);

    }

    void StatsTestsQ7::test_mean_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;

        q7_t *refp  = ref.ptr();

        q7_t *outp  = output.ptr();

        arm_mean_q7(inp,
              inputA.nbSamples(),
              &result);

        outp[0] = result;

        ASSERT_SNR(result,refp[this->refOffset],(float32_t)5);

        ASSERT_NEAR_EQ(result,refp[this->refOffset],ABS_ERROR_Q7);

    }

    void StatsTestsQ7::test_power_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q31_t result;

        q31_t *refp  = refPower.ptr();

        q31_t *outp  = outputPower.ptr();

        arm_power_q7(inp,
              inputA.nbSamples(),
              &result);

        outp[0] = result;

        ASSERT_SNR(result,refp[this->refOffset],(float32_t)SNR_THRESHOLD);

        ASSERT_NEAR_EQ(result,refp[this->refOffset],(q31_t)ABS_ERROR_Q31);

    }

#if 0
/*

Those functions do not yet exist in CMSIS-DSP.
But the tests are kept for when they will be available.

*/
    void StatsTestsQ7::test_rms_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;

        q7_t *refp  = ref.ptr();

        q7_t *outp  = output.ptr();

        arm_rms_q7(inp,
              inputA.nbSamples(),
              &result);

        outp[0] = result;

        ASSERT_SNR(result,refp[this->refOffset],(float32_t)SNR_THRESHOLD);

        ASSERT_NEAR_EQ(result,refp[this->refOffset],ABS_ERROR_Q7);

    }

    void StatsTestsQ7::test_std_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;

        q7_t *refp  = ref.ptr();

        q7_t *outp  = output.ptr();

        arm_std_q7(inp,
              inputA.nbSamples(),
              &result);

        outp[0] = result;

        ASSERT_SNR(result,refp[this->refOffset],(float32_t)SNR_THRESHOLD);

        ASSERT_NEAR_EQ(result,refp[this->refOffset],ABS_ERROR_Q7);

    }

    void StatsTestsQ7::test_var_q7()
    {
        const q7_t *inp  = inputA.ptr();

        q7_t result;

        q7_t *refp  = ref.ptr();

        q7_t *outp  = output.ptr();

        arm_var_q7(inp,
              inputA.nbSamples(),
              &result);

        outp[0] = result;

        ASSERT_SNR(result,refp[this->refOffset],(float32_t)SNR_THRESHOLD);

        ASSERT_NEAR_EQ(result,refp[this->refOffset],ABS_ERROR_Q7);

    }

#endif
  
    void StatsTestsQ7::setUp(Testing::testID_t id,std::vector<Testing::param_t>& paramsArgs,Client::PatternMgr *mgr)
    {
        switch(id)
        {
            case StatsTestsQ7::TEST_MAX_Q7_1:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               maxIndexes.reload(StatsTestsQ7::MAXINDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MAXVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_MAX_Q7_2:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               maxIndexes.reload(StatsTestsQ7::MAXINDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MAXVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_MAX_Q7_3:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               maxIndexes.reload(StatsTestsQ7::MAXINDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MAXVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 2;
            }
            break;

            /*

            For MEAN tests, INPUT2 pattern is used.
            It contains only positive values and prevent the average
            value from being too close to zero which make the estimation
            of the errors difficult.

            */
            case StatsTestsQ7::TEST_MEAN_Q7_4:
            {
               inputA.reload(StatsTestsQ7::INPUT2_Q7_ID,mgr,15);
              
               ref.reload(StatsTestsQ7::MEANVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_MEAN_Q7_5:
            {
               inputA.reload(StatsTestsQ7::INPUT2_Q7_ID,mgr,32);
              
               ref.reload(StatsTestsQ7::MEANVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_MEAN_Q7_6:
            {
               inputA.reload(StatsTestsQ7::INPUT2_Q7_ID,mgr,33);
              
               ref.reload(StatsTestsQ7::MEANVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 2;
            }
            break;

            case StatsTestsQ7::TEST_MIN_Q7_7:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               minIndexes.reload(StatsTestsQ7::MININDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MINVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_MIN_Q7_8:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               minIndexes.reload(StatsTestsQ7::MININDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MINVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_MIN_Q7_9:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               minIndexes.reload(StatsTestsQ7::MININDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MINVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 2;
            }
            break;

            case StatsTestsQ7::TEST_POWER_Q7_10:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               refPower.reload(StatsTestsQ7::POWERVALS_Q31_ID,mgr);
               
               outputPower.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_POWER_Q7_11:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               refPower.reload(StatsTestsQ7::POWERVALS_Q31_ID,mgr);
               
               outputPower.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_POWER_Q7_12:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               refPower.reload(StatsTestsQ7::POWERVALS_Q31_ID,mgr);
               
               outputPower.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 2;
            }
            break;

#if 0
/*

Those functions do not yet exist in CMSIS-DSP.
But the tests are kept for when they will be available.

*/
            case StatsTestsQ7::TEST_RMS_Q7_13:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               ref.reload(StatsTestsQ7::RMSVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_RMS_Q7_14:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               ref.reload(StatsTestsQ7::RMSVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_RMS_Q7_15:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               ref.reload(StatsTestsQ7::RMSVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 2;
            }
            break;

            case StatsTestsQ7::TEST_STD_Q7_16:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               ref.reload(StatsTestsQ7::STDVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_STD_Q7_17:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               ref.reload(StatsTestsQ7::STDVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_STD_Q7_18:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               ref.reload(StatsTestsQ7::STDVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 2;
            }
            break;

            case StatsTestsQ7::TEST_VAR_Q7_19:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,15);
              
               ref.reload(StatsTestsQ7::VARVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 0;
            }
            break;

            case StatsTestsQ7::TEST_VAR_Q7_20:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,32);
              
               ref.reload(StatsTestsQ7::VARVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 1;
            }
            break;

            case StatsTestsQ7::TEST_VAR_Q7_21:
            {
               inputA.reload(StatsTestsQ7::INPUT1_Q7_ID,mgr,33);
              
               ref.reload(StatsTestsQ7::VARVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);

               refOffset = 2;
            }
            break;
#endif

            case StatsTestsQ7::TEST_MAX_Q7_13:
            {
               inputA.reload(StatsTestsQ7::MAXINDEXMAX_Q7_ID,mgr,280);
              
               maxIndexes.reload(StatsTestsQ7::MAXINDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MAXVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 3;
            }
            break;

            case StatsTestsQ7::TEST_MIN_Q7_14:
            {
               inputA.reload(StatsTestsQ7::MININDEXMAX_Q7_ID,mgr,280);
              
               minIndexes.reload(StatsTestsQ7::MININDEXES_S16_ID,mgr);
               ref.reload(StatsTestsQ7::MINVALS_Q7_ID,mgr);
               
               output.create(1,StatsTestsQ7::OUT_Q7_ID,mgr);
               index.create(1,StatsTestsQ7::OUT_S16_ID,mgr);

               refOffset = 3;
            }
            break;
          
        }
        
    }

    void StatsTestsQ7::tearDown(Testing::testID_t id,Client::PatternMgr *mgr)
    {
      switch(id)
      {
            case StatsTestsQ7::TEST_MAX_Q7_1:
            case StatsTestsQ7::TEST_MAX_Q7_2:
            case StatsTestsQ7::TEST_MAX_Q7_3:
            case StatsTestsQ7::TEST_MIN_Q7_7:
            case StatsTestsQ7::TEST_MIN_Q7_8:
            case StatsTestsQ7::TEST_MIN_Q7_9:
            case StatsTestsQ7::TEST_MAX_Q7_13:
            case StatsTestsQ7::TEST_MIN_Q7_14:
              index.dump(mgr);
              output.dump(mgr);
            break;

            case TEST_POWER_Q7_10:
            case TEST_POWER_Q7_11:
            case TEST_POWER_Q7_12:
              outputPower.dump(mgr);
            break;

            default:
              output.dump(mgr);
      }
    }
