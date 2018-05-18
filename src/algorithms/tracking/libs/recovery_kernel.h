
#include <volk/volk.h>
#include <memory>
#include <string.h>

const float REC_FAC = 0.96;

class recovery_kernel
{
   public:
     void gen( float init_phase, float incm_phase,
               unsigned chunk_length,
	       const lv_32fc_t corr_result,
               std::shared_ptr<lv_32fc_t> ref_sig,
	       lv_32fc_t* out,
               int symb_id);
     void put0s(lv_32fc_t* out,int length) {memset(out,0,sizeof(lv_32fc_t) * length);}
     recovery_kernel()  {subframe3 = std::shared_ptr<float> (new float[1600]);}
     ~recovery_kernel() {}
     std::shared_ptr<float> subframe3; 
   private:
     lv_32fc_t d_ampl_est; 
     int symb_id;
};
