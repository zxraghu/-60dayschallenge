#include "sysmon_us/inc/imagermon/imager_mon_emb_lines_extract.hpp"
#include "vfc/core/vfc_math.hpp"

   
namespace imager_mon
{
 
    CParseEmbLine::CParseEmbLine(vfc::uint32_t f_imagehigher,vfc::uint32_t f_imagelower ):m_value(0.0F),m_embdata(0U)
    {
        transform(f_imagehigher,f_imagelower);
        
    }
    CParseEmbLine::CParseEmbLine():m_value(0.0F),
                                     m_embdata(0U)
    {

    }
    CParseEmbLine::CParseEmbLine(vfc::uint32_t f_image):m_value(0.0F), m_embdata(0U)
    {
        
        
            m_embdata=(f_image & 0x00000FF0) >> (4);
            

    }
    void CParseEmbLine::transform(vfc::uint32_t f_embLinePxlHigher,vfc::uint32_t f_embLinePxlLower)
    {
        //The embedded line contains in information in the sequence of bytes. voltage and temperature information are stored in 2 byte format. 
        //both the pixels contain informationin this format (eg: 0X00800080 , where 08 is the data)
        //Higher byte is extracted from f_embLinePxlHigher and lower byte is extracted from f_embLinePxlLower 
        m_embdata= ((f_embLinePxlHigher & 0x00000FF0) << (4)) | ((f_embLinePxlLower & 0x00000FF0) >> (4));
        
    }
    void CParseEmbLine ::convertVolt()
    {
        m_value=((static_cast<vfc::float32_t>(m_embdata)*6/g_voltageConversion));
    }
    void CParseEmbLine::convertVoltOfs()
    {
        //offset value is only last three bytes if m_embdata. offset voltage is calculated by X*6/g_offsetVoltageConversion
        m_value=((static_cast<vfc::float32_t>(m_embdata & 0x0FFF)*6)/g_offsetVoltageConversion);
        // the offest is negative if the highest nibble is holds value of 8
        if((m_embdata & 0xF000)==0x8000)
        {
            m_value*=-1.0F;
        }

    }
    vfc::float32_t CParseEmbLine:: convertTemp()
    {
        // temperature value is negative if the m_embdatafrom embedded line is greater than 0XC000 .Then its converted by subtracting it by 0xC000
        if(m_embdata > g_tempSign)
        {
            m_embdata=m_embdata-g_tempSign;
            tempchange(m_embdata);
            m_value*=-1.0F;
        }
        else
        {
             tempchange(m_embdata);
        }
         return m_value;
        

    }
    void CParseEmbLine::tempchange(vfc::uint32_t f_temp)
    {
        // Higher two bytes are converted to float and added with 1/255 of the lower 2 bytes for temperature calculation
        m_value=static_cast<vfc::float32_t>((m_embdata & 0XFF00) >> 8)+(static_cast<vfc::float32_t>(m_embdata & 0X00FF))/255.F;

    }
   
    CParseEmbLine CParseEmbLine::getMostcommon(const vfc::TCArray<CParseEmbLine, g_vddMeasureTotal>  &f_volt_list)
    {
        vfc::uint8_t l_tempcount = 1U;
        vfc::uint8_t  l_maxCount = 1U;
        vfc::float32_t  l_maxValue = 0.0F;
        CParseEmbLine l_mostCommonValue ;
        for (vfc::int32_t i = 0U; i < g_vddMeasureTotal  ; i++)
        {
            l_maxValue = f_volt_list[i].m_value; 
            for (vfc::int32_t j = 0U; j < g_vddMeasureTotal; j++)
            {

                if( ( vfc::isEqual(l_maxValue,f_volt_list[j].m_value)) && (j != i) )
                {
                    l_tempcount++;
                    if (l_tempcount > l_maxCount)
                    {
                        l_maxCount = l_tempcount;
                        l_mostCommonValue.m_value = f_volt_list[i].m_value;

                    }
                }
                else
                {
                    l_tempcount=1U;

                }

            }


        }
        return  l_mostCommonValue;

    }

    vfc::float32_t getVoltage(vfc::TImageView<const uint32_t> f_imageView, CVoltageIndex f_volttype)
    {
        vfc::TCArray<CParseEmbLine, G_NO_OF_SAT_CAM> l_vddmeasure;
        l_vddmeasure[0]=CParseEmbLine(f_imageView(f_volttype.m_voltmeasure1upper,0U),f_imageView(f_volttype.m_voltmeasure1lower,0U));
        l_vddmeasure[0].convertVolt();
        l_vddmeasure[1]=CParseEmbLine(f_imageView(f_volttype.m_voltmeasure2upper,0U),f_imageView(f_volttype.m_voltmeasure2lower,0U));
        l_vddmeasure[1].convertVolt();
        l_vddmeasure[2]=CParseEmbLine(f_imageView(f_volttype.m_voltmeasure3upper,0U),f_imageView(f_volttype.m_voltmeasure3lower,0U));
        l_vddmeasure[2].convertVolt();
        l_vddmeasure[3]=CParseEmbLine(f_imageView(f_volttype.m_voltmeasure4upper,0U),f_imageView(f_volttype.m_voltmeasure4lower,0U));
        l_vddmeasure[3].convertVolt();
        CParseEmbLine  vm_volt_vdd=CParseEmbLine::getMostcommon(l_vddmeasure);
        CParseEmbLine vm_vdd_offset=CParseEmbLine(f_imageView(f_volttype.m_voltoffsupper,0U),f_imageView(f_volttype.m_voltoffslower,0U));
        vm_vdd_offset.convertVoltOfs();
        //  To increase accuracy each of the three voltage measurement blocks will be calibrated at OVT production where the result will be stored into OTP. 
        //  To calculate the real voltage by using the measured values and OTP calibration value(offset)
        return(vm_volt_vdd.getParsedVal()+vm_vdd_offset.getParsedVal());

    } 

    vfc::float32_t getTemp(vfc::TImageView<const uint32_t> f_imageView)
    {
        CParseEmbLine l_temphex=CParseEmbLine(f_imageView(TEMPUPPER,0U),f_imageView(TEMPLOWER,0U));
        return(l_temphex.convertTemp());
        
    }

    vfc::uint8_t getRegisterData(vfc::TImageView<const uint32_t> f_imageView,vfc::int32_t f_register)
    {
        CParseEmbLine l_registerData(f_imageView(f_register,0U));
        return (l_registerData.getEmbData());
        
    }

    
}