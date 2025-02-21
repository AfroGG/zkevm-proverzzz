#include "goldilocks_cubic_extension.hpp"
#include "zhInv.hpp"
#include "starks.hpp"
#include "constant_pols_starks.hpp"
#include "zkevmSteps.hpp"
#include "zkevm.chelpers.step3.parser.hpp"
#include <immintrin.h>

#define AVX_SIZE_ 4

void ZkevmSteps::step3_parser_first_avx(StepsParams &params, uint64_t nrows, uint64_t nrowsBatch)
{
#pragma omp parallel for
     for (uint64_t i = 0; i < nrows; i += nrowsBatch)
     {
          int i_args = 0;
          //__m256i *tmp1 = new __m256i[NTEMP1_];
          // Goldilocks3::Element_avx *tmp3 = new Goldilocks3::Element_avx[NTEMP3_];
          uint64_t offsets1[4], offsets2[4], offsets3[4];
          __m256i tmp1[NTEMP1_];
          Goldilocks3::Element_avx tmp3[NTEMP3_];
          uint64_t numpols = params.pConstPols->numPols();

          for (int kk = 0; kk < NOPS_; ++kk)
          {
               switch (op3[kk])
               {
               case 0:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 1:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 2:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
                    i_args += 3;
                    break;
               }
               case 3:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 4:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 5:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 6:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
                    i_args += 4;
                    break;
               }
               case 7:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 8:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pConstPols->getElement(args3[i_args + 2], i), numpols, numpols);
                    i_args += 3;
                    break;
               }
               case 9:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                         offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
                    }
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), &params.pConstPols->getElement(0, 0), offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 10:
               {
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), Goldilocks::fromU64(args3[i_args + 2]), numpols);
                    i_args += 3;
                    break;
               }
               case 11:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                    }
                    Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), Goldilocks::fromU64(args3[i_args + 4]), offsets1);
                    i_args += 5;
                    break;
               }
               case 12:
               {

                    Goldilocks3::add13_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);

                    i_args += 3;
                    break;
               }
               case 13:
               {
                    Goldilocks3::add1c3c_avx(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 14:
               {
                    Goldilocks3::add13c_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 15:
               {

                    Goldilocks3::add13_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 16:
               {
                    Goldilocks3::add13c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 17:
               {
                    Goldilocks3::add_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 18:
               {

                    Goldilocks3::add33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 19:
               {
                    Goldilocks3::add_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 20:
               {
                    Goldilocks3::add33c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 21:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 22:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 23:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 24:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 25:
               {

                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 26:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
                    i_args += 3;
                    break;
               }
               case 27:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 28:
               {

                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 29:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
                    i_args += 6;
                    break;
               }
               case 30:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 31:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 32:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 33:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * numpols;
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(0, 0), offsets2);
                    i_args += 5;
                    break;
               }
               case 34:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.publicInputs[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 35:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 36:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                         offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 37:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 38:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 39:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], numpols, args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 40:
               {
                    Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 41:
               {
                    Goldilocks3::sub31c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 42:
               {
                    Goldilocks3::sub_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 43:
               {
                    Goldilocks3::sub33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 44:
               {
                    Goldilocks3::sub_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 45:
               {
                    Goldilocks::mult_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 46:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 47:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 48:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 49:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 50:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 51:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                         offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
                    }
                    Goldilocks::mul_avx(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 52:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::mul_avx(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 53:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 54:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
                    i_args += 4;
                    break;
               }
               case 55:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * numpols;
                    }
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pConstPols->getElement(0, 0), offsets1, offsets2);
                    i_args += 6;
                    break;
               }
               case 56:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 57:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 58:
               {
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), tmp1[args3[i_args + 2]], numpols);
                    i_args += 3;
                    break;
               }
               case 59:
               {
                    Goldilocks3::mul13c_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 60:
               {
                    Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pConstPols->getElement(args3[i_args + 1], i), tmp3[args3[i_args + 2]], numpols);
                    i_args += 3;
                    break;
               }
               case 61:
               {

                    Goldilocks3::mul13_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 62:
               {
                    Goldilocks3::mul13c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 63:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks3::mul13c_avx(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 64:
               {
                    Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 65:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = FIELD_EXTENSION * (j + AVX_SIZE_ * args3[i_args + 5]);
                    }
                    Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 66:
               {
                    Goldilocks3::mul1c3c_avx(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), (Goldilocks3::Element &)*params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 67:
               {
                    Goldilocks3::mul13c_avx(tmp3[args3[i_args]], params.x_n[i], (Goldilocks3::Element &)*params.challenges[args3[i_args + 1]], params.x_n.offset());
                    i_args += 2;
                    break;
               }
               case 68:
               {
                    Goldilocks3::mul13_avx(tmp3[args3[i_args]], params.x_n[i], tmp3[args3[i_args + 1]], params.x_n.offset());
                    i_args += 2;
                    break;
               }
               case 69:
               {

                    Goldilocks::Element tmp_inv[3];
                    Goldilocks::Element ti0[4];
                    Goldilocks::Element ti1[4];
                    Goldilocks::Element ti2[4];
                    Goldilocks::store_avx(ti0, tmp3[args3[i_args]][0]);
                    Goldilocks::store_avx(ti1, tmp3[args3[i_args]][1]);
                    Goldilocks::store_avx(ti2, tmp3[args3[i_args]][2]);

                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         tmp_inv[0] = ti0[j];
                         tmp_inv[1] = ti1[j];
                         tmp_inv[2] = ti2[j];
                         Goldilocks3::mul((Goldilocks3::Element &)(params.q_2ns[(i + j) * 3]),
                                          params.zi.zhInv((i + j)),
                                          (Goldilocks3::Element &)tmp_inv);
                    }
                    i_args += 1;
                    break;
               }
               case 70:
               {

                    Goldilocks3::mul33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 1]]);
                    i_args += 3;
                    break;
               }
               case 71:
               {
                    Goldilocks3::mul_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 72:
               {
                    Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 73:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }

                    Goldilocks3::mul33c_avx(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 74:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = FIELD_EXTENSION * (j + AVX_SIZE_ * args3[i_args + 5]);
                    }
                    Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 75:
               {
                    Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 76:
               {
                    Goldilocks3::mul33c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 77:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
                    }
                    Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 78:
               {
                    Goldilocks::copy_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]]);
                    i_args += 2;
                    break;
               }
               case 79:
               {
                    Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], args3[i_args + 2]);
                    i_args += 3;
                    break;
               }
               case 80:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::copy_avx(tmp1[args3[i_args]], &params.pols[0], offsets1);
                    i_args += 5;
                    break;
               }
               case 81:
               {
                    Goldilocks::copy_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]));
                    i_args += 2;
                    break;
               }
               case 82:
               {
                    Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), numpols);
                    i_args += 2;
                    break;
               }
               case 83:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                    }
                    Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), offsets1);
                    i_args += 4;
                    break;
               }
               case 84:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets1);
                    i_args += 6;
                    break;
               }
               case 85:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
                    i_args += 6;
                    break;
               }
               case 86:
               {
                    Goldilocks::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 87:
               {
                    Goldilocks::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 88:
               {
                    Goldilocks3::add13_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 89:
               {
                    Goldilocks3::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp3[args3[i_args + 4]], args3[i_args + 3]);
                    i_args += 5;
                    break;
               }
               case 90:
               {
                    Goldilocks3::add33c_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 91:
               {
                    Goldilocks::copy_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 92:
               {
                    Goldilocks::sub_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 93:
               {
                    Goldilocks::sub_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], Goldilocks::fromU64(args3[i_args + 2]), tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 94:
               {
                    Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 95:
               {
                    Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp1[args3[i_args + 4]], args3[i_args + 3]);
                    i_args += 5;
                    break;
               }
               case 96:
               {
                    Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), numpols);
                    i_args += 4;
                    break;
               }
               case 97:
               {
                    Goldilocks3::sub33c_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 98:
               {
                    Goldilocks3::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 99:
               {
                    Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3], &params.pConstPols->getElement(args3[i_args + 4], i), numpols);
                    i_args += 5;
                    break;
               }
               case 100:
               {
                    Goldilocks::copy_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[(args3[i_args + 2])]);
                    i_args += 3;
                    break;
               }
               case 101:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);

                    i_args += 6;
                    break;
               }
               case 102:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[args3[i_args + 5] + i * args3[i_args + 6]], args3[i_args + 6]);
                    i_args += 7;
                    break;
               }
               case 103:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add13_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 104:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add_avx(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp3[args3[i_args + 6]], args3[i_args + 5]);
                    i_args += 7;
                    break;
               }
               case 105:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add33c_avx(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], params.challenges[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 106:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::sub_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 107:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::sub_avx(&params.pols[0], offsets1, Goldilocks::fromU64(args3[i_args + 4]), tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 108:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 109:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp1[args3[i_args + 6]], args3[i_args + 5]);
                    i_args += 7;
                    break;
               }
               case 110:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pConstPols->getElement(args3[i_args + 5], i), numpols);
                    i_args += 6;
                    break;
               }
               case 111:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                         offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
                    }
                    Goldilocks::mul_avx(&params.pols[0], offsets1, &params.pConstPols->getElement(0, 0), tmp1[args3[i_args + 7]], offsets2);
                    i_args += 8;
                    break;
               }
               case 112:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::mul_avx(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 113:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::copy_avx(&params.pols[0], offsets1, tmp1[(args3[i_args + 4])]);
                    i_args += 5;
                    break;
               }
               case 114:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[0], offsets2);
                    i_args += 9;
                    break;
               }
               case 115:
               {
                    // 0, 50
                    Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 116:
               {
                    Goldilocks3::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
               i_args += 4;
               break;
               }
               case 117:
               {
                    Goldilocks::copy_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 118:
               {
                    Goldilocks::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3], &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], args3[i_args + 5]);
                    i_args += 6;
                    break;
               }
               case 119:
               {
                    for (uint64_t j = 0; j < AVX_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                         offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * args3[i_args + 7];
                         offsets3[j] = args3[i_args + 8] + (((i + j) + args3[i_args + 9]) % args3[i_args + 10]) * numpols;

                    }
                    Goldilocks::mul_avx(&params.pols[0], offsets1, &params.pols[0], &params.pConstPols->getElement(0, 0), offsets2, offsets3);
                    i_args += 11;
                    break;
               }
               case 120: 
               {
                    Goldilocks3::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp3[args3[i_args + 4]], args3[i_args + 3]);
                    i_args += 5;
                    break;
               }
               default:
               {
                    std::cout << " Wrong operation in step3_first!" << op3[kk] << std::endl;
                    exit(1);
               }
               }
          }
          if (i_args != NARGS_)
               std::cout << " " << i_args << " - " << NARGS_ << std::endl;
          assert(i_args == NARGS_);
          // delete (tmp1);
          // delete (tmp3);
     }
}
void ZkevmSteps::step3_parser_first(StepsParams &params, uint64_t nrows, uint64_t nrowsBatch)
{
}

void ZkevmSteps::step3_parser_first_avx_jump(StepsParams &params, uint64_t nrows, uint64_t nrowsBatch)
{

     void (*jumpTable[])(int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols) = {

         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 0:
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 1:
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 2:
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 3:
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 4:
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 5:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
              }
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 9;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 6:
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 7:
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 8:
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pConstPols->getElement(args3[i_args + 2], i), numpols, numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 9:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                   offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
              }
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), &params.pConstPols->getElement(0, 0), offsets1, offsets2);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 10:
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), Goldilocks::fromU64(args3[i_args + 2]), numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 11:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
              }
              Goldilocks::add_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), Goldilocks::fromU64(args3[i_args + 4]), offsets1);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 12:
              Goldilocks3::add13_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);

              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 13:
              Goldilocks3::add1c3c_avx(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 14:
              Goldilocks3::add13c_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 15:
              Goldilocks3::add13_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 16:
              Goldilocks3::add13c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 17:
              Goldilocks3::add_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 18:
              Goldilocks3::add33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 19:
              Goldilocks3::add_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 20:
              Goldilocks3::add33c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 21:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 22:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 23:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 24:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 25:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 26:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 27:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 28:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 29:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 30:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 31:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[0], offsets2);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 32:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 33:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * numpols;
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(0, 0), offsets2);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 34:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.publicInputs[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 35:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 36:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                   offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 37:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 38:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
              }
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 9;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 39:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], numpols, args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 40:
              Goldilocks::sub_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 41:
              Goldilocks3::sub31c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 42:
              Goldilocks3::sub_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 43:
              Goldilocks3::sub33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 44:
              Goldilocks3::sub_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 45:
              Goldilocks::mult_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 46:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 47:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 48:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 49:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 50:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 51:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                   offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
              }
              Goldilocks::mul_avx(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 52:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
              }
              Goldilocks::mul_avx(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 9;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 53:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 54:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 55:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (i + j) * numpols;
              }
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], &params.pConstPols->getElement(0, 0), offsets1, offsets2);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 56:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 57:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
              }
              Goldilocks::mul_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 58:
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), tmp1[args3[i_args + 2]], numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 59:
              Goldilocks3::mul13c_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 60:
              Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pConstPols->getElement(args3[i_args + 1], i), tmp3[args3[i_args + 2]], numpols);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 61:
              Goldilocks3::mul13_avx(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 62:
              Goldilocks3::mul13c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 63:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks3::mul13c_avx(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 64:
              Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 65:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = FIELD_EXTENSION * (j + AVX_SIZE_ * args3[i_args + 5]);
              }
              Goldilocks3::mul13_avx(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 66:
              Goldilocks3::mul1c3c_avx(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), (Goldilocks3::Element &)*params.challenges[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 67:
              Goldilocks3::mul13c_avx(tmp3[args3[i_args]], params.x_n[i], (Goldilocks3::Element &)*params.challenges[args3[i_args + 1]], params.x_n.offset());
              i_args += 2;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 68:
              Goldilocks3::mul13_avx(tmp3[args3[i_args]], params.x_n[i], tmp3[args3[i_args + 1]], params.x_n.offset());
              i_args += 2;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 69:
              Goldilocks::Element tmp_inv[3];
              Goldilocks::Element ti0[4];
              Goldilocks::Element ti1[4];
              Goldilocks::Element ti2[4];
              Goldilocks::store_avx(ti0, tmp3[args3[i_args]][0]);
              Goldilocks::store_avx(ti1, tmp3[args3[i_args]][1]);
              Goldilocks::store_avx(ti2, tmp3[args3[i_args]][2]);

              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   tmp_inv[0] = ti0[j];
                   tmp_inv[1] = ti1[j];
                   tmp_inv[2] = ti2[j];
                   Goldilocks3::mul((Goldilocks3::Element &)(params.q_2ns[(i + j) * 3]),
                                    params.zi.zhInv((i + j)),
                                    (Goldilocks3::Element &)tmp_inv);
              }
              i_args += 1;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 70:
              Goldilocks3::mul33c_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 1]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 71:
              Goldilocks3::mul_avx(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 72:
              Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 73:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }

              Goldilocks3::mul33c_avx(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 74:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = FIELD_EXTENSION * (j + AVX_SIZE_ * args3[i_args + 5]);
              }
              Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 75:
              Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 76:
              Goldilocks3::mul33c_avx(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 77:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                   offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
              }
              Goldilocks3::mul_avx(tmp3[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 78:
              Goldilocks::copy_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]]);
              i_args += 2;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 79:
              Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], args3[i_args + 2]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 80:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks::copy_avx(tmp1[args3[i_args]], &params.pols[0], offsets1);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 81:
              Goldilocks::copy_avx(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]));
              i_args += 2;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 82:
              Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), numpols);
              i_args += 2;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 83:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
              }
              Goldilocks::copy_avx(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), offsets1);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 84:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
              }
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 85:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
              }
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 86:
              Goldilocks::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 87:
              Goldilocks::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 4]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 88:
              Goldilocks3::add13_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 89:
              Goldilocks3::add_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp3[args3[i_args + 4]], args3[i_args + 3]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 90:
              Goldilocks3::add33c_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 91:
              assert(0);
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 92:
              Goldilocks::sub_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 93:
              Goldilocks::sub_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], Goldilocks::fromU64(args3[i_args + 2]), tmp1[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 94:
              Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 95:
              Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp1[args3[i_args + 4]], args3[i_args + 3]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 96:
              Goldilocks::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), numpols);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 97:
              assert(0);
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 98:
              Goldilocks3::mul_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
              i_args += 4;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 99:
              assert(0);
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 100:
              Goldilocks::copy_avx(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[(args3[i_args + 2])]);
              i_args += 3;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 101:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);

              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 102:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[args3[i_args + 5] + i * args3[i_args + 6]], args3[i_args + 6]);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 103:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks3::add13_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 104:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks3::add_avx(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp3[args3[i_args + 6]], args3[i_args + 5]);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 105:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks3::add33c_avx(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], params.challenges[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 106:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::sub_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 107:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::sub_avx(&params.pols[0], offsets1, Goldilocks::fromU64(args3[i_args + 4]), tmp1[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 108:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::mul_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 109:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::mul_avx(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp1[args3[i_args + 6]], args3[i_args + 5]);
              i_args += 7;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 110:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::mul_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pConstPols->getElement(args3[i_args + 5], i), numpols);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 111:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                   offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
              }
              Goldilocks::mul_avx(&params.pols[0], offsets1, &params.pConstPols->getElement(0, 0), tmp1[args3[i_args + 7]], offsets2);
              i_args += 8;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 112:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks3::mul_avx(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
              i_args += 6;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 113:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
              }
              Goldilocks::copy_avx(&params.pols[0], offsets1, tmp1[(args3[i_args + 4])]);
              i_args += 5;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 114:
              for (uint64_t j = 0; j < AVX_SIZE_; ++j)
              {
                   offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                   offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
              }
              Goldilocks::add_avx(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[0], offsets2);
              i_args += 9;
         },
         [](int i, int &i_args, __m256i tmp1[NTEMP1_], Goldilocks3::Element_avx tmp3[NTEMP3_], uint64_t offsets1[4], uint64_t offsets2[4], StepsParams &params, const int numpols)
         {
              // 115:
              // 0, 50
              Goldilocks::add_avx(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
              i_args += 3;
              Goldilocks::mul_avx(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
              i_args += 5;
         }};

     double t1 = omp_get_wtime();
#pragma omp parallel for
     for (uint64_t i = 0; i < nrows; i += nrowsBatch)
     {
          int i_args = 0;
          uint64_t offsets1[4], offsets2[4];
          __m256i tmp1[NTEMP1_];
          Goldilocks3::Element_avx tmp3[NTEMP3_];
          uint64_t numpols = params.pConstPols->numPols();
          // 2.43172
          // 1.26495
          for (int kk = 0; kk < NOPS_; ++kk)
          {
               jumpTable[op3[kk]](i, i_args, tmp1, tmp3, offsets1, offsets2, params, numpols);
          }
          assert(i_args == NARGS_);
     }
     double t2 = omp_get_wtime();
     std::cout << "time= " << t2 - t1 << std::endl;
}

#ifdef __AVX512__
void ZkevmSteps::step3_parser_first_avx512(StepsParams &params, uint64_t nrows, uint64_t nrowsBatch)
{
#pragma omp parallel for
     for (uint64_t i = 0; i < nrows; i += nrowsBatch)
     {
          int i_args = 0;
          //__m256i *tmp1 = new __m256i[NTEMP1_];
          // Goldilocks3::Element_avx *tmp3 = new Goldilocks3::Element_avx[NTEMP3_];
          uint64_t offsets1[AVX512_SIZE_], offsets2[AVX512_SIZE_];
          __m512i tmp1[NTEMP1_];
          Goldilocks3::Element_avx512 tmp3[NTEMP3_];
          uint64_t numpols = params.pConstPols->numPols();

          for (int kk = 0; kk < NOPS_; ++kk)
          {
               switch (op3[kk])
               {
               case 0:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 1:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 2:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
                    i_args += 3;
                    break;
               }
               case 3:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 4:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 5:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 6:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
                    i_args += 4;
                    break;
               }
               case 7:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 8:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pConstPols->getElement(args3[i_args + 2], i), numpols, numpols);
                    i_args += 3;
                    break;
               }
               case 9:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                         offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
                    }
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), &params.pConstPols->getElement(0, 0), offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 10:
               {
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), Goldilocks::fromU64(args3[i_args + 2]), numpols);
                    i_args += 3;
                    break;
               }
               case 11:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                    }
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), Goldilocks::fromU64(args3[i_args + 4]), offsets1);
                    i_args += 5;
                    break;
               }
               case 12:
               {

                    Goldilocks3::add13_avx512(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);

                    i_args += 3;
                    break;
               }
               case 13:
               {
                    Goldilocks3::add1c3c_avx512(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 14:
               {
                    Goldilocks3::add13c_avx512(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 15:
               {

                    Goldilocks3::add13_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 16:
               {
                    Goldilocks3::add13c_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 17:
               {
                    Goldilocks3::add_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 18:
               {

                    Goldilocks3::add33c_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 19:
               {
                    Goldilocks3::add_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 20:
               {
                    Goldilocks3::add33c_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 21:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 22:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 23:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 24:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 25:
               {

                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 26:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], Goldilocks::fromU64(args3[i_args + 2]));
                    i_args += 3;
                    break;
               }
               case 27:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 28:
               {

                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 29:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
                    i_args += 6;
                    break;
               }
               case 30:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 31:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 32:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 33:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * numpols;
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pConstPols->getElement(0, 0), offsets2);
                    i_args += 5;
                    break;
               }
               case 34:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.publicInputs[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 35:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 36:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                         offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 37:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 38:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 39:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], numpols, args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 40:
               {
                    Goldilocks::sub_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 41:
               {
                    Goldilocks3::sub31c_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], Goldilocks::fromU64(args3[i_args + 3]), args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 42:
               {
                    Goldilocks3::sub_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 43:
               {
                    Goldilocks3::sub33c_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 44:
               {
                    Goldilocks3::sub_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 45:
               {
                    Goldilocks::mult_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 46:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 47:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp1[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 48:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[0], tmp1[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 49:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pConstPols->getElement(args3[i_args + 2], i), numpols);
                    i_args += 3;
                    break;
               }
               case 50:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 51:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (i + j) * args3[i_args + 2];
                         offsets2[j] = args3[i_args + 3] + (((i + j) + args3[i_args + 4]) % args3[i_args + 5]) * args3[i_args + 6];
                    }
                    Goldilocks::mul_avx512(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 52:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::mul_avx512(tmp1[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 9;
                    break;
               }
               case 53:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]), &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 54:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), args3[i_args + 2], numpols);
                    i_args += 4;
                    break;
               }
               case 55:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * numpols;
                    }
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[0], &params.pConstPols->getElement(0, 0), offsets1, offsets2);
                    i_args += 6;
                    break;
               }
               case 56:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], args3[i_args + 3]);
                    i_args += 4;
                    break;
               }
               case 57:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets2[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets2);
                    i_args += 6;
                    break;
               }
               case 58:
               {
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), tmp1[args3[i_args + 2]], numpols);
                    i_args += 3;
                    break;
               }
               case 59:
               {
                    Goldilocks3::mul13c_avx512(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 60:
               {
                    Goldilocks3::mul13_avx512(tmp3[args3[i_args]], &params.pConstPols->getElement(args3[i_args + 1], i), tmp3[args3[i_args + 2]], numpols);
                    i_args += 3;
                    break;
               }
               case 61:
               {

                    Goldilocks3::mul13_avx512(tmp3[args3[i_args]], tmp1[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 62:
               {
                    Goldilocks3::mul13c_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 63:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks3::mul13c_avx512(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 64:
               {
                    Goldilocks3::mul13_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 65:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = FIELD_EXTENSION * (j + AVX512_SIZE_ * args3[i_args + 5]);
                    }
                    Goldilocks3::mul13_avx512(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 66:
               {
                    Goldilocks3::mul1c3c_avx512(tmp3[args3[i_args]], Goldilocks::fromU64(args3[i_args + 1]), (Goldilocks3::Element &)*params.challenges[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 67:
               {
                    Goldilocks3::mul13c_avx512(tmp3[args3[i_args]], params.x_n[i], (Goldilocks3::Element &)*params.challenges[args3[i_args + 1]], params.x_n.offset());
                    i_args += 2;
                    break;
               }
               case 68:
               {
                    Goldilocks3::mul13_avx512(tmp3[args3[i_args]], params.x_n[i], tmp3[args3[i_args + 1]], params.x_n.offset());
                    i_args += 2;
                    break;
               }
               case 69:
               {

                    Goldilocks::Element tmp_inv[3];
                    Goldilocks::Element ti0[AVX512_SIZE_];
                    Goldilocks::Element ti1[AVX512_SIZE_];
                    Goldilocks::Element ti2[AVX512_SIZE_];
                    Goldilocks::store_avx512(ti0, tmp3[args3[i_args]][0]);
                    Goldilocks::store_avx512(ti1, tmp3[args3[i_args]][1]);
                    Goldilocks::store_avx512(ti2, tmp3[args3[i_args]][2]);

                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         tmp_inv[0] = ti0[j];
                         tmp_inv[1] = ti1[j];
                         tmp_inv[2] = ti2[j];
                         Goldilocks3::mul((Goldilocks3::Element &)(params.q_2ns[(i + j) * 3]),
                                          params.zi.zhInv((i + j)),
                                          (Goldilocks3::Element &)tmp_inv);
                    }
                    i_args += 1;
                    break;
               }
               case 70:
               {

                    Goldilocks3::mul33c_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 1]]);
                    i_args += 3;
                    break;
               }
               case 71:
               {
                    Goldilocks3::mul_avx512(tmp3[args3[i_args]], tmp3[args3[i_args + 1]], tmp3[args3[i_args + 2]]);
                    i_args += 3;
                    break;
               }
               case 72:
               {
                    Goldilocks3::mul_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 73:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }

                    Goldilocks3::mul33c_avx512(tmp3[args3[i_args]], &params.pols[0], params.challenges[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 74:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = FIELD_EXTENSION * (j + AVX512_SIZE_ * args3[i_args + 5]);
                    }
                    Goldilocks3::mul_avx512(tmp3[args3[i_args]], &params.pols[0], tmp3[args3[i_args + 5]], offsets1);
                    i_args += 6;
                    break;
               }
               case 75:
               {
                    Goldilocks3::mul_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], tmp3[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 76:
               {
                    Goldilocks3::mul33c_avx512(tmp3[args3[i_args]], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], params.challenges[args3[i_args + 3]], args3[i_args + 2]);
                    i_args += 4;
                    break;
               }
               case 77:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                         offsets2[j] = args3[i_args + 5] + (i + j) * args3[i_args + 6];
                    }
                    Goldilocks3::mul_avx512(tmp3[args3[i_args]], &params.pols[0], &params.pols[0], offsets1, offsets2);
                    i_args += 7;
                    break;
               }
               case 78:
               {
                    Goldilocks::copy_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]]);
                    i_args += 2;
                    break;
               }
               case 79:
               {
                    Goldilocks::copy_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], args3[i_args + 2]);
                    i_args += 3;
                    break;
               }
               case 80:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::copy_avx512(tmp1[args3[i_args]], &params.pols[0], offsets1);
                    i_args += 5;
                    break;
               }
               case 81:
               {
                    Goldilocks::copy_avx512(tmp1[(args3[i_args])], Goldilocks::fromU64(args3[i_args + 1]));
                    i_args += 2;
                    break;
               }
               case 82:
               {
                    Goldilocks::copy_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(args3[i_args + 1], i), numpols);
                    i_args += 2;
                    break;
               }
               case 83:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * numpols;
                    }
                    Goldilocks::copy_avx512(tmp1[(args3[i_args])], &params.pConstPols->getElement(0, 0), offsets1);
                    i_args += 4;
                    break;
               }
               case 84:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 2] + (((i + j) + args3[i_args + 3]) % args3[i_args + 4]) * args3[i_args + 5];
                    }
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], &params.pols[0], offsets1);
                    i_args += 6;
                    break;
               }
               case 85:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args + 1] + (((i + j) + args3[i_args + 2]) % args3[i_args + 3]) * args3[i_args + 4];
                    }
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[0], Goldilocks::fromU64(args3[i_args + 5]), offsets1);
                    i_args += 6;
                    break;
               }
               case 86:
               {
                    Goldilocks::add_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 87:
               {
                    Goldilocks::add_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               case 88:
               {
                    Goldilocks3::add13_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 89:
               {
                    Goldilocks3::add_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp3[args3[i_args + 4]], args3[i_args + 3]);
                    i_args += 5;
                    break;
               }
               case 90:
               {
                    Goldilocks3::add33c_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], params.challenges[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 91:
               {
                    assert(0); // code not used
                    i_args += 4;
                    break;
               }
               case 92:
               {
                    Goldilocks::sub_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 93:
               {
                    Goldilocks::sub_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], Goldilocks::fromU64(args3[i_args + 2]), tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 94:
               {
                    Goldilocks::mul_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], tmp1[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 95:
               {
                    Goldilocks::mul_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], &params.pols[args3[i_args + 2] + i * args3[i_args + 3]], tmp1[args3[i_args + 4]], args3[i_args + 3]);
                    i_args += 5;
                    break;
               }
               case 96:
               {
                    Goldilocks::mul_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[args3[i_args + 2]], &params.pConstPols->getElement(args3[i_args + 3], i), numpols);
                    i_args += 4;
                    break;
               }
               case 97:
               {
                    assert(0); // code not used
                    i_args += 4;
                    break;
               }
               case 98:
               {
                    Goldilocks3::mul_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp3[args3[i_args + 2]], tmp3[args3[i_args + 3]]);
                    i_args += 4;
                    break;
               }
               case 99:
               {
                    assert(0); // code not used
                    i_args += 4;
                    break;
               }
               case 100:
               {
                    Goldilocks::copy_avx512(&params.pols[args3[i_args] + i * args3[i_args + 1]], args3[i_args + 1], tmp1[(args3[i_args + 2])]);
                    i_args += 3;
                    break;
               }
               case 101:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::add_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);

                    i_args += 6;
                    break;
               }
               case 102:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::add_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[args3[i_args + 5] + i * args3[i_args + 6]], args3[i_args + 6]);
                    i_args += 7;
                    break;
               }
               case 103:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add13_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 104:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add_avx512(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp3[args3[i_args + 6]], args3[i_args + 5]);
                    i_args += 7;
                    break;
               }
               case 105:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::add33c_avx512(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], params.challenges[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 106:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::sub_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 107:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::sub_avx512(&params.pols[0], offsets1, Goldilocks::fromU64(args3[i_args + 4]), tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 108:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], tmp1[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 109:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx512(&params.pols[0], offsets1, &params.pols[args3[i_args + 4] + i * args3[i_args + 5]], tmp1[args3[i_args + 6]], args3[i_args + 5]);
                    i_args += 7;
                    break;
               }
               case 110:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::mul_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pConstPols->getElement(args3[i_args + 5], i), numpols);
                    i_args += 6;
                    break;
               }
               case 111:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                         offsets2[j] = args3[i_args + 4] + (((i + j) + args3[i_args + 5]) % args3[i_args + 6]) * numpols;
                    }
                    Goldilocks::mul_avx512(&params.pols[0], offsets1, &params.pConstPols->getElement(0, 0), tmp1[args3[i_args + 7]], offsets2);
                    i_args += 8;
                    break;
               }
               case 112:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks3::mul_avx512(&params.pols[0], offsets1, tmp3[args3[i_args + 4]], tmp3[args3[i_args + 5]]);
                    i_args += 6;
                    break;
               }
               case 113:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                    }
                    Goldilocks::copy_avx512(&params.pols[0], offsets1, tmp1[(args3[i_args + 4])]);
                    i_args += 5;
                    break;
               }
               case 114:
               {
                    for (uint64_t j = 0; j < AVX512_SIZE_; ++j)
                    {
                         offsets1[j] = args3[i_args] + (((i + j) + args3[i_args + 1]) % args3[i_args + 2]) * args3[i_args + 3];
                         offsets2[j] = args3[i_args + 5] + (((i + j) + args3[i_args + 6]) % args3[i_args + 7]) * args3[i_args + 8];
                    }
                    Goldilocks::add_avx512(&params.pols[0], offsets1, tmp1[args3[i_args + 4]], &params.pols[0], offsets2);
                    i_args += 9;
                    break;
               }
               case 115:
               {
                    // 0, 50
                    Goldilocks::add_avx512(tmp1[(args3[i_args])], tmp1[args3[i_args + 1]], tmp1[args3[i_args + 2]]);
                    i_args += 3;
                    Goldilocks::mul_avx512(tmp1[(args3[i_args])], &params.pols[args3[i_args + 1] + i * args3[i_args + 2]], &params.pols[args3[i_args + 3] + i * args3[i_args + 4]], args3[i_args + 2], args3[i_args + 4]);
                    i_args += 5;
                    break;
               }
               default:
               {
                    std::cout << " Wrong operation in step3_first!" << op3[kk] << std::endl;
                    exit(1);
               }
               }
          }
          if (i_args != NARGS_)
               std::cout << " " << i_args << " - " << NARGS_ << std::endl;
          assert(i_args == NARGS_);
          // delete (tmp1);
          // delete (tmp3);
     }
}
#endif
