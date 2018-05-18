#include "recovery_kernel.h"
#include <cmath>
#include <complex>

void recovery_kernel::gen(  float init_phase,
                            float incm_phase,
			    unsigned chunk_length,
			    const lv_32fc_t corr_result,
                            std::shared_ptr<lv_32fc_t> ref_sig,
			    lv_32fc_t* out)
{
   lv_32fc_t  norm;
   lv_32fc_t* in =  ref_sig.get();

   d_ampl_est += abs(real(corr_result));
   d_ampl_est *= REC_FAC;
	    
   volk_32fc_x2_conjugate_dot_prod_32fc(
   		                        &norm,
				        in,
				        in,
				        chunk_length
				        );
	    
   volk_32fc_s32fc_multiply_32fc(out,
				 in,
				 d_ampl_est_est*(1-REC_FAC)/ real(norm),
				 chunk_length
				);

   lv_32fc_t incm = std::exp(lv_32fc_t(0,incm_phase));
	    
   volk_32fc_s32fc_x2_rotator_32fc(out,
                                   out,
				   std::exp(lv_32fc_t(0,init_phase),
				   incm,
				   chunk_length
				  ); 
}






