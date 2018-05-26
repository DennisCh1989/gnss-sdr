
#include <volk/volk.h>
#include <memory>
#include <string.h>
#include <cinttypes>

const float REC_FAC = 0.9;

class recovery_kernel
{
   public:
     unsigned int gen( float init_phase, float incm_phase,
                       unsigned chunk_length,
	               const lv_32fc_t corr_result,
                       std::shared_ptr<lv_32fc_t> ref_sig,
	               lv_32fc_t* out,
                       int symb_id);
     void put0s(lv_32fc_t* out,int length) {memset(out,0,sizeof(lv_32fc_t) * length);}
     unsigned int clear_rec_ker(lv_32fc_t* out);
     recovery_kernel(int vector_length) {d_in = new lv_32fc_t[vector_length*40];}
     ~recovery_kernel() {delete [] d_in;} 
   private:
     float d_ampl_est; 
     unsigned int d_symb_length;
     float d_symb_ampl;
     lv_32fc_t* d_in;
};
