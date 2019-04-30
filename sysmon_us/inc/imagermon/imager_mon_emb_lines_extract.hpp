#ifndef IMAGER_MON_EMB_LINES_EXTRACT
#define IMAGER_MON_EMB_LINES_EXTRACT
#include "vfc/inc/core/vfc_types.hpp"
#include "vfc/container/vfc_carray.hpp"
#include "vfc/inc/image/vfc_imageview.hpp"
#include "sysmon_us_cfg/inc/imager_mon_cfg.hpp"
namespace imager_mon
{
    //--------------------------------------------------------------------------------------------------------------
    //! @brief Structure that holds voltages(avdd,dovdd and dvdd) and temperature from the camera
    //--------------------------------------------------------------------------------------------------------------
    struct CCamData
    {
        vfc::float32_t m_avdd;
        vfc::float32_t m_dovdd;
        vfc::float32_t m_dvdd; 
        vfc::float32_t m_temp;
        vfc::uint8_t m_watchdog_top_2;
        vfc::uint8_t m_watchdog_top_3;
    };
    //--------------------------------------------------------------------------------------------------------------
    //! @brief enumerator that holds the position of voltages and temperature in embedded line.
    //--------------------------------------------------------------------------------------------------------------
    enum EEmbLinePosition : vfc::int32_t
    {
        AVDDMEASURE1UPPER   =17,
        AVDDMEASURE1LOWER   =21,
        AVDDMEASURE2UPPER   =25,
        AVDDMEASURE2LOWER   =29,
        AVDDMEASURE3UPPER   =33,
        AVDDMEASURE3LOWER   =37,
        AVDDMEASURE4UPPER   =41,
        AVDDMEASURE4LOWER   =45,
        AVDDOFFSETUPPER     =49,
        AVDDOFFSETLOWER     =53,
        DOVDDMEASURE1UPPER  =57,
        DOVDDMEASURE1LOWER  =61,
        DOVDDMEASURE2UPPER  =65,
        DOVDDMEASURE2LOWER  =69,
        DOVDDMEASURE3UPPER  =73,
        DOVDDMEASURE3LOWER  =77,
        DOVDDMEASURE4UPPER  =81,
        DOVDDMEASURE4LOWER  =85,
        DOVDDOFFSETUPPER    =89,
        DOVDDOFFSETLOWER    =93,
        DVDDMEASURE1UPPER   =97,
        DVDDMEASURE1LOWER   =101,
        DVDDMEASURE2UPPER   =105,
        DVDDMEASURE2LOWER   =109,
        DVDDMEASURE3UPPER   =113,
        DVDDMEASURE3LOWER   =117,
        DVDDMEASURE4UPPER   =121,
        DVDDMEASURE4LOWER   =125,
        DVDDOFFSETUPPER     =129,
        DVDDOFFSETLOWER     =133,
        WATCHDOG_TOP_2      =153,
        WATCHDOG_TOP_3      =157,
        TEMPUPPER           =161,
        TEMPLOWER           =165

    };
    enum EWacthDogStatus : vfc::int32_t
    {
        WATCHDOG_STATUS_PASSED=0,
        WATCHDOG_STATUS_FAILED=1
    };
    enum EWacthDogBitPosition : vfc::uint8_t
    {
        WATCHDOG_BIT_0=0x01,
        WATCHDOG_BIT_1=0x02,
        WATCHDOG_BIT_2=0x04,
        WATCHDOG_BIT_3=0x08,
        WATCHDOG_BIT_4=0x10,
        WATCHDOG_BIT_5=0x20,
        WATCHDOG_BIT_6=0x40,
        WATCHDOG_BIT_7=0x80
    };
    //--------------------------------------------------------------------------------------------------------------
    //! @brief structure with voltage position of voltages and temperature in embedded line.
    //--------------------------------------------------------------------------------------------------------------
    struct CVoltageIndex{
        EEmbLinePosition m_voltmeasure1upper;
        EEmbLinePosition m_voltmeasure1lower;
        EEmbLinePosition m_voltmeasure2upper;
        EEmbLinePosition m_voltmeasure2lower;
        EEmbLinePosition m_voltmeasure3upper;
        EEmbLinePosition m_voltmeasure3lower;
        EEmbLinePosition m_voltmeasure4upper;
        EEmbLinePosition m_voltmeasure4lower;
        EEmbLinePosition m_voltoffsupper;
        EEmbLinePosition m_voltoffslower;

    };
    // avdd voltage position in embedded line
    const CVoltageIndex avdd_voltage={AVDDMEASURE1UPPER,AVDDMEASURE1LOWER ,AVDDMEASURE2UPPER,AVDDMEASURE2LOWER,AVDDMEASURE3UPPER,AVDDMEASURE3LOWER,AVDDMEASURE4UPPER,AVDDMEASURE4LOWER,AVDDOFFSETUPPER,AVDDOFFSETLOWER};
    // dvdd voltage position in embedded line
    const CVoltageIndex dvdd_voltage={DVDDMEASURE1UPPER,DVDDMEASURE1LOWER ,DVDDMEASURE2UPPER,DVDDMEASURE2LOWER,DVDDMEASURE3UPPER,DVDDMEASURE3LOWER,DVDDMEASURE4UPPER,DVDDMEASURE4LOWER,DVDDOFFSETUPPER,DVDDOFFSETLOWER};
    // dovdd voltage position in embedded line
    const CVoltageIndex dovdd_voltage={DOVDDMEASURE1UPPER,DOVDDMEASURE1LOWER ,DOVDDMEASURE2UPPER,DOVDDMEASURE2LOWER,DOVDDMEASURE3UPPER,DOVDDMEASURE3LOWER,DOVDDMEASURE4UPPER,DOVDDMEASURE4LOWER,DOVDDOFFSETUPPER,DOVDDOFFSETLOWER};
    //--------------------------------------------------------------------------------------------------------------
    //! @brief Class parses voltages and temp from the embedded line
    //--------------------------------------------------------------------------------------------------------------
    class CParseEmbLine
    {
        public:
        //--------------------------------------------------------------------------------------------------------------
        //! @brief Constructor that takes embedded line pixel and convert to 2 byte data
        //! f_imagehigher pixel that holds the higher 16 bytes 
        //! f_imagelower  pixel that holds the lower 16 bytes
        //--------------------------------------------------------------------------------------------------------------
        CParseEmbLine(vfc::uint32_t f_imagehigher,vfc::uint32_t f_imagelower );
        //--------------------------------------------------------------------------------------------------------------
        //! @brief Constructor that takes embedded line pixel and convert to 2 byte data
        //! f_imagehigher pixel that holds the higher 16 bytes 
        //! f_imagelower  pixel that holds the lower 16 bytes
        //--------------------------------------------------------------------------------------------------------------
        CParseEmbLine(vfc::uint32_t f_image );
        //--------------------------------------------------------------------------------------------------------------
        //! @brief default constructor
        //--------------------------------------------------------------------------------------------------------------
        CParseEmbLine();
        //--------------------------------------------------------------------------------------------------------------
        //! @brief convert 4 byte data from embdded lines to voltage
        //--------------------------------------------------------------------------------------------------------------
        void convertVolt();
        //--------------------------------------------------------------------------------------------------------------
        //! @brief convert 4 byte data from embdded lines to voltage for offset
        //--------------------------------------------------------------------------------------------------------------
        void convertVoltOfs();
        //--------------------------------------------------------------------------------------------------------------
        //! @brief Makes the temperature negative or positive by checking the 4th Byte value
        //--------------------------------------------------------------------------------------------------------------
        vfc::float32_t convertTemp();
        //--------------------------------------------------------------------------------------------------------------
        //! @brief Due to a bug within imager (collision handling Voltage monitor register updating / reading) a special procedure within the SOC Software need to be implemented for getting Vxxx_meas voltages.
        //! VAVDD_meas:  Get out one of two or more identical values from {VAVDD_meas1,VAVDD_meas2,VAVDD_meas3,VAVDD_meas4}
        //! VDOVDD_meas:  Get out one of two or more identical values from  {VDOVDD_meas1,VDOVDD_meas2,VDOVDD_meas3,VDOVDD_meas4}
        //! VVDD_meas:  Get out one of two or more identical values from  {VVDD_meas1,VVDD_meas2,VVDD_meas3,VVDD_meas4}
        //! @param[in] f_volt_list : This holds the 4 voltage values
        //! @retval returns the mpost common value among the 4 voltages.
        //--------------------------------------------------------------------------------------------------------------
        static CParseEmbLine getMostcommon(const vfc::TCArray<CParseEmbLine,G_NO_OF_SAT_CAM>  &f_volt_list);
        //--------------------------------------------------------------------------------------------------------------
        //! @brief This function transforms the pixels into 4 byte data by removed the paddind added
        //! @retval returns the parsed voltage or temperature after converting
        //--------------------------------------------------------------------------------------------------------------
        vfc::float32_t getParsedVal() const
        {
            return m_value;
        }
        vfc::float32_t getEmbData() const
        {
            return m_embdata;
        }
        private:
        //--------------------------------------------------------------------------------------------------------------
        //! @brief This function transforms the pixels into 4 byte data by removed the paddind added
        //! @param[in] f_embLinePxlHigher pixel that holds the higher 16 bytes 
        //! @param[in] f_embLinePxlLower  pixel that holds the lower 16 bytes
        //--------------------------------------------------------------------------------------------------------------
        void transform(vfc::uint32_t f_embLinePxlHigher,vfc::uint32_t f_embLinePxlLower);
        //--------------------------------------------------------------------------------------------------------------
        //! @brief convert 2 byte data from embeddedlines to Temperature
        //! @param[in] f_temp temperature in 2 byte format
        //--------------------------------------------------------------------------------------------------------------
        void tempchange(vfc::uint32_t f_temp);
        //! embeddedLine information after removing padding     
        vfc::uint32_t m_embdata;
        //! converted temp/volt values
        vfc::float32_t m_value;
    };

    //--------------------------------------------------------------------------------------------------------------
    //! @brief Function to get the volatge from embedded line
    //! @param[in] f_imageView embeddedLine data 
    //! @param[in] f_volttype holds which voltage it is (avdd,dvdd,dovdd)
    //--------------------------------------------------------------------------------------------------------------
    vfc::float32_t getVoltage(vfc::TImageView<const vfc::uint32_t> f_imageView,CVoltageIndex f_volttype);
    //--------------------------------------------------------------------------------------------------------------
    //! @brief Function to get the temperature from embedded line
    // @param[in] f_imageView pixel information with temp data
    //--------------------------------------------------------------------------------------------------------------
    vfc::float32_t getTemp(vfc::TImageView<const uint32_t> f_imageView);
    //--------------------------------------------------------------------------------------------------------------
    //! @brief Function to read register values from embeddedLine
    // @param[in] f_imageView pixel information with temp data
    // @param[in] f_register Register address that needs to read
    //--------------------------------------------------------------------------------------------------------------
    vfc::uint8_t getRegisterData(vfc::TImageView<const uint32_t> f_imageView,vfc::int32_t f_register);
    ///! the voltages are stored in 15 bits . offset voltage calculatrion is done by X*6V/32768
    constexpr vfc::float32_t g_offsetVoltageConversion = 32768.F;
    //! the voltages are stored in 12 bits , so it will map to 0(0V)-12^2(6V). So final voltage caculation is X*6V/4096
    constexpr vfc::float32_t g_voltageConversion = 4096.F;
    //! If the read {0x4F06, 0x4F07} ≤0xC000, the temperature is positive. 
    //! If the read {0x4F06, 0x4F07} > 0xC000, the temperature is negative. The read value needs to be converted by subtracting it by 0xC000.
    constexpr vfc::uint32_t g_tempSign = 0xC000;
    //! Embedded lines will be sending all the 4 values for avdd,dvdd, and dovdd, The acutal volatge will be the one of the two or more identical values in it. 
    constexpr vfc::uint8_t g_vddMeasureTotal = 4U;
    //To be removed once EVM is available
    struct CPumDebug
    {
        bool dtpr_failed;
        bool internal_register_failed;
        bool atpr_failed;
        bool unique_id_failed;
        bool array_addresscheck_failed;
        bool online_pixelTest_failed;
    };
    
}//imager_mon namespace
#endif
