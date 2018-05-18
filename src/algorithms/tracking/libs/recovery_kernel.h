
#include <volk/volk.h>
#include <memory>
#include <string.h>

const float REC_FAC = 0.96;

class recovery_kernel
{
   public:
     void gen(lv_32fc_t* out,bool valid);
     void put0s(lv_32fc_t* out,int length) {memset(out,0,sizeof(lv_32fc_t) * length);}
     recovery_kernel()  {}
     ~recovery_kernel() {}
   private:
     lv_32fc_t d_ampl_est; 
};
