/**
 * @file:       AdaptorFrameTypes.h
 *              
 * Purpose:     Defines the frame types that are used by the toolbox.
 *              
 * $Authors:    David T., Chris P., Uday Mandhata $
 *              
 * Copyright 2005-2012 The MathWorks, Inc.
 *
 */

#ifndef __ADAPTOR_FRAME_TYPES_H__
#define __ADAPTOR_FRAME_TYPES_H__

#define NUMBANDS(num) ((num & 0xFF) << 16)			

namespace imaqkit {
    namespace frametypes {
        enum FRAMETYPE_DEFINITIONS {
            // bit flags to for each frame class.
            RGB24_CLASS        = 0x01000000,
            MONOCHROME_CLASS   = 0x11000000,
            RGBPLANAR_CLASS    = 0x02000000,
            YUVPACKED_CLASS    = 0x03000000,
            YUVPLANAR_CLASS    = 0x04000000,
            RGB16_CLASS        = 0x05000000,
            BAYER_CLASS        = 0x06000000,
            YUVHYBRID_CLASS    = 0x07000000,
            FLIP_CLASS         = 0x100
        };

	enum FRAME_DATA_TYPE {
		// Type to be returned by getNativeDataType()
		// The return value from getNativeDataType() is used
		// as input to ArrayUtil::getMxNativeDataType() to extract the native MATLAB type.
		UINT8_TYPE,					
		INT8_TYPE,
		UINT16_TYPE,
		INT16_TYPE,
		UINT32_TYPE,
		INT32_TYPE,
		SINGLE_TYPE,
		DOUBLE_TYPE
	};
		
        enum FRAMETYPE {
            UNKNOWN_FRAMETYPE = 0x0000,             // should be avoided whenever possible.
            ADAPTOR = 0x0001,             // adaptor supplied frame object

            //////////////////////// Monochrome Formats ///////////////////////

            // top-down image
            MONO8         = MONOCHROME_CLASS | NUMBANDS(1) | 0x0,   // 8-bit monochrome
            MONO10        = MONOCHROME_CLASS | NUMBANDS(1) | 0x1,   // 10-bit monochrome
            MONO12        = MONOCHROME_CLASS | NUMBANDS(1) | 0x2,   // 12-bit monochrome
            MONO14        = MONOCHROME_CLASS | NUMBANDS(1) | 0x3,   // 14-bit monochrome
            MONO16        = MONOCHROME_CLASS | NUMBANDS(1) | 0x4,   // 16-bit monochrome
            MONO10_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x5,// 10-bit monochrome
            MONO12_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x6,// 12-bit monochrome
            MONO14_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x7,// 14-bit monochrome
            MONO16_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x8,// 16-bit monochrome
            SIGNED_INT16           = MONOCHROME_CLASS | NUMBANDS(1) | 0x9, // Signed 16-bit monochrome
            SIGNED_INT32           = MONOCHROME_CLASS | NUMBANDS(1) | 0x10, // Signed 32-bit monochrome
            SIGNED_INT16_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x11, // Signed 16-bit monochrome
            SIGNED_INT32_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x12, // Signed 32-bit monochrome
            FLOAT                  = MONOCHROME_CLASS | NUMBANDS(1) | 0x13, // Single precision floating point
            DOUBLE                 = MONOCHROME_CLASS | NUMBANDS(1) | 0x14, // Double precision floating point
            FLOAT_BIGENDIAN        = MONOCHROME_CLASS | NUMBANDS(1) | 0x15, // Single precision floating point
            DOUBLE_BIGENDIAN       = MONOCHROME_CLASS | NUMBANDS(1) | 0x16, // Double precision floating point
            SIGNED_INT8            = MONOCHROME_CLASS | NUMBANDS(1) | 0x17, // Signed 8-bit monochrome
            MONO10_PACKED          = MONOCHROME_CLASS | NUMBANDS(1) | 0x18, // Packs two 10-bit pixels into three bytes
            MONO12_PACKED          = MONOCHROME_CLASS | NUMBANDS(1) | 0x19, // Packs two 12-bit pixels into three bytes
            MONO8_INV              = MONOCHROME_CLASS | NUMBANDS(1) | 0x1a, // Inverted 8-bit monochrome, 255 is black, 0 is white
            MONO9        = MONOCHROME_CLASS | NUMBANDS(1) | 0x1b,   // 9-bit monochrome
            MONO11        = MONOCHROME_CLASS | NUMBANDS(1) | 0x1c,   // 11-bit monochrome
            MONO13        = MONOCHROME_CLASS | NUMBANDS(1) | 0x1d,   // 13-bit monochrome
            MONO15        = MONOCHROME_CLASS | NUMBANDS(1) | 0x1e,   // 15-bit monochrome
            MONO9_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x1f,// 9-bit monochrome
            MONO11_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x20,// 11-bit monochrome
            MONO13_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x21,// 13-bit monochrome
            MONO15_BIGENDIAN = MONOCHROME_CLASS | NUMBANDS(1) | 0x22,// 15-bit monochrome

            // bottom-up image
            MONO8_FLIP    = MONO8 | FLIP_CLASS,   // 8-bit monochrome
            MONO10_FLIP   = MONO10 | FLIP_CLASS,   // 10-bit monochrome
            MONO12_FLIP   = MONO12 | FLIP_CLASS,   // 12-bit monochrome
            MONO14_FLIP   = MONO14 | FLIP_CLASS,   // 14-bit monochrome
            MONO16_FLIP   = MONO16 | FLIP_CLASS,   // 16-bit monochrome
            MONO9_FLIP    = MONO9 | FLIP_CLASS,   // 9-bit monochrome
            MONO11_FLIP   = MONO11 | FLIP_CLASS,   // 11-bit monochrome
            MONO13_FLIP   = MONO13 | FLIP_CLASS,   // 13bit monochrome
            MONO15_FLIP   = MONO15 | FLIP_CLASS,   // 15-bit monochrome
            MONO10_BIGENDIAN_FLIP = MONO10_BIGENDIAN | FLIP_CLASS,// 10-bit monochrome
            MONO12_BIGENDIAN_FLIP = MONO12_BIGENDIAN | FLIP_CLASS,// 12-bit monochrome
            MONO14_BIGENDIAN_FLIP = MONO14_BIGENDIAN | FLIP_CLASS,// 14-bit monochrome
            MONO16_BIGENDIAN_FLIP = MONO16_BIGENDIAN | FLIP_CLASS,// 16-bit monochrome
            MONO9_BIGENDIAN_FLIP = MONO9_BIGENDIAN | FLIP_CLASS,// 9-bit monochrome
            MONO11_BIGENDIAN_FLIP = MONO11_BIGENDIAN | FLIP_CLASS,// 11-bit monochrome
            MONO13_BIGENDIAN_FLIP = MONO13_BIGENDIAN | FLIP_CLASS,// 13-bit monochrome
            MONO15_BIGENDIAN_FLIP = MONO15_BIGENDIAN | FLIP_CLASS,// 15-bit monochrome
            SIGNED_INT16_FLIP = SIGNED_INT16 | FLIP_CLASS, // Signed 16-bit monochrome
            SIGNED_INT32_FLIP = SIGNED_INT32 | FLIP_CLASS, // Signed 32-bit monochrome
            SIGNED_INT16_BIGENDIAN_FLIP = SIGNED_INT16_BIGENDIAN | FLIP_CLASS, // Signed 16-bit monochrome
            SIGNED_INT32_BIGENDIAN_FLIP = SIGNED_INT32_BIGENDIAN | FLIP_CLASS, // Signed 32-bit monochrome
            FLOAT_FLIP    = FLOAT | FLIP_CLASS,  // Single precision floating point
            DOUBLE_FLIP   = DOUBLE | FLIP_CLASS, // Double precision floating point
            FLOAT_BIGENDIAN_FLIP    = FLOAT_BIGENDIAN | FLIP_CLASS,  // Single precision floating point
            DOUBLE_BIGENDIAN_FLIP   = DOUBLE_BIGENDIAN | FLIP_CLASS, // Double precision floating point
            SIGNED_INT8_FLIP        = SIGNED_INT8 | FLIP_CLASS, // Signed 8-bit monochrome


            //////////////////////// Packed RGB Formats ///////////////////////

            // top-down image
            RGB8          = MONO8,                             // RGB8, really a mono type, can be used for indexed palates
            RGB24_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x0,   // RGB (24-bit) packed in R-G-B ordering
            BGR24_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x1,   // RGB (24-bit) packed in B-G-R ordering
            RGB32_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x2,   // RGB (32-bit) packed in R-G-B-X ordering
            BGR32_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x3,   // RGB (32-bit) packed in B-G-R-X ordering
            XRGB32_PACKED = RGB24_CLASS | NUMBANDS(3) | 0x4,   // aRGB (32-bit) packed in X-R-G-B ordering
            ARGB32        = XRGB32_PACKED,                     // aRGB (32-bit) packed in X-R-G-B ordering
            XBGR32_PACKED = RGB24_CLASS | NUMBANDS(3) | 0x5,   // aBGR (32-bit) packed in X-B-G-R ordering
            ABGR32        = XBGR32_PACKED,                     // aBGR (32-bit) packed in X-B-G-R ordering
            RGB48_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x6,   // RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED  = RGB24_CLASS | NUMBANDS(3) | 0x7,   // RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_BIGENDIAN = RGB24_CLASS | NUMBANDS(3) | 0x8, // RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_BIGENDIAN = RGB24_CLASS | NUMBANDS(3) | 0x9, // RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_SIGNED    = RGB24_CLASS | NUMBANDS(3) | 0xA, // Signed RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_SIGNED    = RGB24_CLASS | NUMBANDS(3) | 0xB, // Signed RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_SIGNED_BIGENDIAN = RGB24_CLASS | NUMBANDS(3) | 0xC, // Signed RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_SIGNED_BIGENDIAN = RGB24_CLASS | NUMBANDS(3) | 0xD, // Signed RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB10_PACKED = RGB24_CLASS | NUMBANDS(3) | 0xE, // RGB (48-bit) with 10 bits precision per pixel with each color occupying two bytes
            BGR10_PACKED = RGB24_CLASS | NUMBANDS(3) | 0xF, // BGR (48-bit) with 10 bits precision per pixel with each color occupying two bytes
            RGB12_PACKED = RGB24_CLASS | NUMBANDS(3) | 0x10, // RGB (48-bit) with 12 bits precision per pixel with each color occupying two bytes
            BGR12_PACKED = RGB24_CLASS | NUMBANDS(3) | 0x11, // BGR (48-bit) with 12 bits precision per pixel with each color occupying two bytes
            RGB555        = RGB16_CLASS | NUMBANDS(3) | 0x0,   // RGB 5:5:5 (16-bit) bit-packed
            ARGB1555      = RGB555,                            // RGB 5:5:5 (16-bit) bit-packed
            RGB565        = RGB16_CLASS | NUMBANDS(3) | 0x1,   // RGB 5:6:5 (16-bit) bit-packed
            ARGB4444      = RGB16_CLASS | NUMBANDS(3) | 0x2,   // RGB 4:4:4 (16-bit) bit-packed
            A2R10G10B10   = RGB16_CLASS | NUMBANDS(3) | 0x3,   // RGB 10:10:10 (32-bit) bit-packed with 2 alpha bits leading
            A2B10G10R10   = RGB16_CLASS | NUMBANDS(3) | 0x4,   // BGR 10:10:10 (32-bit) bit-packed with 2 alpha bits leading
            R10G10B10A2   = RGB16_CLASS | NUMBANDS(3) | 0x5,   // RGB 10:10:10 (32-bit) bit-packed with 2 alpha bits trailing
            B10G10R10A2   = RGB16_CLASS | NUMBANDS(3) | 0x6,   // BGR 10:10:10 (32-bit) bit-packed with 2 alpha bits trailing
            R2G2B2BGR = RGB16_CLASS | NUMBANDS(3) | 0x7, // (deprecated) Packed BGR in the format R2G2B2 followed by B8G8R8 (deprecated)
            R8G8B8xxB2G2R2 = RGB16_CLASS | NUMBANDS(3) | 0x8, // Packed RGB in the format R8G8B8 followed by 2 alpha bits and then followed by B2G2R2

            // bottom-up image //   
            RGB8_FLIP         = RGB8 | FLIP_CLASS,        // RGB8, really a mono type, can be used for indexed palates
            RGB24_PACKED_FLIP = RGB24_PACKED | FLIP_CLASS,// RGB 24-bit packed in R-G-B ordering
            BGR24_PACKED_FLIP = BGR24_PACKED | FLIP_CLASS,// RGB 24-bit packed in B-G-R ordering
            RGB32_PACKED_FLIP = RGB32_PACKED | FLIP_CLASS,// RGB 32-bit packed in R-G-B-X ordering
            BGR32_PACKED_FLIP = BGR32_PACKED | FLIP_CLASS,// RGB 32-bit packed in B-G-R-X ordering
            XRGB32_PACKED_FLIP = XRGB32_PACKED | FLIP_CLASS, //aRGB (32-bit) packed in X-R-G-B ordering
            ARGB32_FLIP       = ARGB32 | FLIP_CLASS,      //aRGB (32-bit) packed in X-R-G-B ordering
            XBGR32_PACKED_FLIP = XBGR32_PACKED | FLIP_CLASS, //aBGR (32-bit) packed in X-B-G-R ordering
            ABGR32_FLIP       = ABGR32 | FLIP_CLASS,      //aBGR (32-bit) packed in X-B-G-R ordering
            RGB48_PACKED_FLIP = RGB48_PACKED | FLIP_CLASS, // RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_FLIP = BGR48_PACKED | FLIP_CLASS, // RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_BIGENDIAN_FLIP = RGB48_PACKED_BIGENDIAN | FLIP_CLASS, // RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_BIGENDIAN_FLIP = BGR48_PACKED_BIGENDIAN | FLIP_CLASS, // RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_SIGNED_FLIP    = RGB48_PACKED_SIGNED | FLIP_CLASS, // Signed RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_SIGNED_FLIP    = BGR48_PACKED_SIGNED | FLIP_CLASS, // Signed RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB48_PACKED_SIGNED_BIGENDIAN_FLIP = RGB48_PACKED_SIGNED_BIGENDIAN | FLIP_CLASS, // Signed RGB (48-bit) packed in R-G-B ordering (2 bytes per color)
            BGR48_PACKED_SIGNED_BIGENDIAN_FLIP = BGR48_PACKED_SIGNED_BIGENDIAN | FLIP_CLASS, // Signed RGB (48-bit) packed in B-G-R ordering (2 bytes per color)
            RGB555_FLIP   = RGB555 | FLIP_CLASS,   // RGB 5:5:5 (16-bit) bit-packed
            ARGB1555_FLIP = ARGB1555 | FLIP_CLASS, // RGB 5:5:5 (16-bit) bit-packed
            RGB565_FLIP   = RGB565 | FLIP_CLASS,   // RGB 5:6:5 (16-bit) bit-packed
            ARGB4444_FLIP = ARGB4444 | FLIP_CLASS, // RGB 4:4:4 (16-bit) bit-packed
            A2R10G10B10_FLIP = A2R10G10B10 | FLIP_CLASS,   // RGB 10:10:10 (32-bit) bit-packed
            A2B10G10R10_FLIP = A2B10G10R10 | FLIP_CLASS,   // BGR 10:10:10 (32-bit) bit-packed

            //////////////////////// Planar RGB Formats ///////////////////////

            // top-down image
            RGB24_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x0,    // RGB (24-bit) planar image
            RGB48_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x1,    // RGB (48-bit) planar image
            RGB48_PLANAR_BIGENDIAN = RGBPLANAR_CLASS | NUMBANDS(3) | 0x2,    // RGB (48-bit) planar image
            RGB48_SIGNED_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x3,
            RGB48_SIGNED_PLANAR_BIGENDIAN = RGBPLANAR_CLASS | NUMBANDS(3) | 0x4,
            RGB10_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x5, // RGB planar image with 10 bits per band per pixel
            RGB12_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x6, // RGB planar image with 12 bits per band per pixel
            RGB14_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x7, // RGB planar image with 14 bits per band per pixel
            RGB24_SIGNED_PLANAR = RGBPLANAR_CLASS | NUMBANDS(3) | 0x8,

            //////////////////////// Bayer Encoded Formats ///////////////////////
            BAYER8_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x0, // Bayer encoded, 8 bits per pixel GRBG sensor alignment
            BAYER8_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x1, // Bayer encoded, 8 bits per pixel GBRG sensor alignment
            BAYER8_BGGR = BAYER_CLASS | NUMBANDS(3) | 0x2, // Bayer encoded, 8 bits per pixel BGGR sensor alignment
            BAYER8_RGGB = BAYER_CLASS | NUMBANDS(3) | 0x3, // Bayer encoded, 8 bits per pixel RGGB sensor alignment
            BAYER10_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x4, // Bayer encoded, 10 bits per pixel GRBG sensor alignment
            BAYER10_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x5, // Bayer encoded, 10 bits per pixel GBRG sensor alignment
            BAYER10_BGGR = BAYER_CLASS | NUMBANDS(3) | 0x6, // Bayer encoded, 10 bits per pixel BGGR sensor alignment
            BAYER10_RGGB = BAYER_CLASS | NUMBANDS(3) | 0x7, // Bayer encoded, 10 bits per pixel RGGB sensor alignment
            BAYER12_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x8, // Bayer encoded, 12 bits per pixel GRBG sensor alignment
            BAYER12_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x9, // Bayer encoded, 12 bits per pixel GBRG sensor alignment
            BAYER12_BGGR = BAYER_CLASS | NUMBANDS(3) | 0xa, // Bayer encoded, 12 bits per pixel BGGR sensor alignment
            BAYER12_RGGB = BAYER_CLASS | NUMBANDS(3) | 0xb, // Bayer encoded, 12 bits per pixel RGGB sensor alignment
            BAYER14_GRBG = BAYER_CLASS | NUMBANDS(3) | 0xc, // Bayer encoded, 14 bits per pixel GRBG sensor alignment
            BAYER14_GBRG = BAYER_CLASS | NUMBANDS(3) | 0xd, // Bayer encoded, 14 bits per pixel GBRG sensor alignment
            BAYER14_BGGR = BAYER_CLASS | NUMBANDS(3) | 0xe, // Bayer encoded, 14 bits per pixel BGGR sensor alignment
            BAYER14_RGGB = BAYER_CLASS | NUMBANDS(3) | 0xf, // Bayer encoded, 14 bits per pixel RGGB sensor alignment
            BAYER16_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x10, // Bayer encoded, 16 bits per pixel GRBG sensor alignment
            BAYER16_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x11, // Bayer encoded, 16 bits per pixel GBRG sensor alignment
            BAYER16_BGGR = BAYER_CLASS | NUMBANDS(3) | 0x12, // Bayer encoded, 16 bits per pixel BGGR sensor alignment
            BAYER16_RGGB = BAYER_CLASS | NUMBANDS(3) | 0x13, // Bayer encoded, 16 bits per pixel RGGB sensor alignment
            BAYER10_PACKED_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x14, // Bayer encoded, packed into three bytes for two pixels, 10 bits per pixel GRBG sensor alignment
            BAYER10_PACKED_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x15, // Bayer encoded, packed into three bytes for two pixels, 10 bits per pixel GBRG sensor alignment
            BAYER10_PACKED_BGGR = BAYER_CLASS | NUMBANDS(3) | 0x16, // Bayer encoded, packed into three bytes for two pixels, 10 bits per pixel BGGR sensor alignment
            BAYER10_PACKED_RGGB = BAYER_CLASS | NUMBANDS(3) | 0x17, // Bayer encoded, packed into three bytes for two pixels, 10 bits per pixel RGGB sensor alignment
            BAYER12_PACKED_GRBG = BAYER_CLASS | NUMBANDS(3) | 0x18, // Bayer encoded, packed into three bytes for two pixels, 12 bits per pixel GRBG sensor alignment
            BAYER12_PACKED_GBRG = BAYER_CLASS | NUMBANDS(3) | 0x19, // Bayer encoded, packed into three bytes for two pixels, 12 bits per pixel GBRG sensor alignment
            BAYER12_PACKED_BGGR = BAYER_CLASS | NUMBANDS(3) | 0x1a, // Bayer encoded, packed into three bytes for two pixels, 12 bits per pixel BGGR sensor alignment
            BAYER12_PACKED_RGGB = BAYER_CLASS | NUMBANDS(3) | 0x1b, // Bayer encoded, packed into three bytes for two pixels, 12 bits per pixel RGGB sensor alignment

            //////////////////////// YUV Packed Formats ///////////////////////

            YUV_YUY2 = YUVPACKED_CLASS | NUMBANDS(3) | 0x0,        // YUYV packed format
            YUV_UYVY = YUVPACKED_CLASS | NUMBANDS(3) | 0x1,        // UYVY packed format (aka Y422)
            YUV_YVYU = YUVPACKED_CLASS | NUMBANDS(3) | 0x2,        // UYVY packed format
            YUV_IYU1 = YUVPACKED_CLASS | NUMBANDS(3) | 0x3,        // 12-bit YUV 4:1:1, IEEE 1394 DC Spec
            YUV_IYU2 = YUVPACKED_CLASS | NUMBANDS(3) | 0x4,        // 24-bit YUV 4:4:4, IEEE 1394 DC Spec
            YUV_Y41P = YUVPACKED_CLASS | NUMBANDS(3) | 0x5,        // YUV 4:1:1 in UYVYUYVYYYYY packed format
            YUV_IUY2 = YUVPACKED_CLASS | NUMBANDS(3) | 0x6,        // Like IYU2, but with VUY ordering.  Used by the Coreco adaptor.


            //////////////////////// YUV Hybrid Formats ///////////////////////
            YUV_M420 = YUVHYBRID_CLASS | NUMBANDS(3) | 0x0,        // Packed YUV 4:2:0, M420 format for Microsoft Lifecam Studio.
            
            //////////////////////// YUV Planar Formats ///////////////////////

            YUV_YVU9 = YUVPLANAR_CLASS | NUMBANDS(3) | 0x0,        // YVU 4:1:1 planar format
            YUV_YV12 = YUVPLANAR_CLASS | NUMBANDS(3) | 0x1,        // YUV 4:2:0 planar (Y, U, V plane order)
            YUV_I420 = YUVPLANAR_CLASS | NUMBANDS(3) | 0x2         // YUV 4:2:0 planar (Y, V, U plane order)
        };
    }

    namespace colorspaces {
        enum COLORSPACE {
            OTHER = 0,
            MONOCHROME = 1,
            RGB = 2,
            YCbCr = 4,
            BAYER = 8
        };
    }

    namespace bayer {
        enum SENSOR_ALIGNMENT {
            GRBG = 0,
            GBRG = 1,
            BGGR = 2,
            RGGB = 4
        };
    }	
}

#endif
