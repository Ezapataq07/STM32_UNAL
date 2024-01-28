#include "sine_model_data.h"

ai_handle ai_sine_model_data_weights_get(void)
{

  AI_ALIGNED(4)
  static const ai_u8 s_sine_model_weights[ 1284 ] = {
    0xcf, 0x46, 0xa6, 0x3e, 0x70, 0xf1, 0x10, 0xbe, 0x08, 0x07,
    0x10, 0x3f, 0x4d, 0xea, 0x08, 0x3f, 0x18, 0x6f, 0x05, 0x3f,
    0x3c, 0x42, 0x3b, 0xbe, 0x2c, 0xbd, 0xfe, 0xbd, 0x0b, 0x67,
    0xe6, 0xbe, 0x15, 0xfa, 0xdc, 0xbb, 0x86, 0x5e, 0xda, 0x3e,
    0x5c, 0x26, 0x03, 0xbe, 0x39, 0x35, 0xaa, 0xbe, 0x9a, 0x0e,
    0x30, 0xbe, 0xd0, 0x6b, 0x15, 0xbf, 0x70, 0x4c, 0x0d, 0x3f,
    0x3f, 0x3f, 0x3c, 0x3e, 0x3c, 0x82, 0x26, 0x3f, 0x00, 0x00,
    0x00, 0x00, 0x78, 0x05, 0x9f, 0xbe, 0xf6, 0xdc, 0x9a, 0xbf,
    0x19, 0x7e, 0x42, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x94, 0x97, 0xc3, 0xbc,
    0xc1, 0x53, 0x26, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xa5, 0xc2, 0xa8, 0xbd, 0x9e, 0x02, 0x90, 0xbe, 0xfa, 0x9b,
    0x30, 0x3e, 0x24, 0x5f, 0xbd, 0xbe, 0xc5, 0xf1, 0xaf, 0x3e,
    0xd6, 0xfe, 0x8c, 0x3d, 0x7f, 0x36, 0x8e, 0xbe, 0x14, 0xca,
    0xdd, 0x3d, 0xf0, 0xaf, 0xff, 0xbc, 0xb0, 0x91, 0x84, 0x3d,
    0x3b, 0x6c, 0x82, 0x3e, 0x99, 0x8d, 0xef, 0x3d, 0x68, 0xa0,
    0x26, 0xbd, 0xe1, 0x6c, 0xa7, 0x3e, 0xba, 0x1b, 0x1a, 0x3e,
    0x1a, 0x24, 0x2d, 0x3e, 0xcd, 0xaf, 0x1e, 0x3e, 0x40, 0x24,
    0xb8, 0xbe, 0xa2, 0xf9, 0x30, 0xbe, 0x58, 0x9f, 0xaa, 0xbe,
    0xfa, 0xc3, 0x5e, 0x3e, 0xf1, 0xfa, 0x05, 0x3f, 0x90, 0xdc,
    0x3b, 0xbe, 0x1c, 0x13, 0xd0, 0xbd, 0xd2, 0x77, 0x35, 0xbe,
    0x2a, 0xc7, 0xa4, 0xbe, 0xf2, 0x0c, 0xe8, 0xbd, 0xde, 0x70,
    0xcc, 0x3e, 0x82, 0x44, 0x38, 0xbe, 0x14, 0xd2, 0xba, 0x3d,
    0xbe, 0x07, 0x99, 0xbe, 0x2a, 0x85, 0x7a, 0x3e, 0xc2, 0x48,
    0x86, 0xbd, 0x77, 0xec, 0x84, 0x3e, 0x3d, 0x72, 0x82, 0x3c,
    0xe4, 0xdf, 0xfc, 0xbd, 0x46, 0x63, 0xd2, 0xbe, 0x5b, 0x1c,
    0xde, 0xbe, 0xe4, 0x3c, 0x12, 0xbe, 0x15, 0x55, 0x95, 0x3e,
    0x73, 0x72, 0xad, 0xbe, 0x1e, 0xd0, 0xb8, 0xbe, 0xe8, 0xaa,
    0x82, 0xbe, 0x6f, 0xce, 0x41, 0x3e, 0xaf, 0x4d, 0xd1, 0x3e,
    0x74, 0x05, 0xfe, 0x3d, 0x74, 0x70, 0x46, 0xbe, 0x11, 0xaf,
    0x83, 0xbe, 0xa6, 0x9b, 0xb6, 0xbf, 0xf4, 0x30, 0x15, 0xbe,
    0xb1, 0x41, 0x42, 0xbe, 0x2d, 0xdc, 0xb9, 0x3e, 0xbb, 0x01,
    0x3b, 0x3e, 0xae, 0xd7, 0x27, 0x3e, 0x1c, 0xb2, 0x2a, 0x3e,
    0xbc, 0xc1, 0x5f, 0xbe, 0x27, 0x4c, 0xa0, 0x3e, 0x66, 0x5c,
    0x9f, 0xbe, 0x6c, 0x0e, 0x3c, 0xbe, 0x7e, 0x3c, 0xb3, 0x3e,
    0x82, 0xf4, 0x27, 0xbe, 0x5d, 0x09, 0x7b, 0xbe, 0xb1, 0x9f,
    0xb6, 0xbe, 0x8e, 0x03, 0x2e, 0x3e, 0x0b, 0x11, 0x2a, 0xbe,
    0x26, 0x75, 0x4f, 0x3d, 0x6c, 0x87, 0x97, 0x3d, 0xfd, 0x6c,
    0xd6, 0x3e, 0x5f, 0xdb, 0x97, 0x3d, 0x0a, 0xbb, 0x3e, 0xbf,
    0x25, 0xad, 0x87, 0xbe, 0xb7, 0x3f, 0xd3, 0xbe, 0x1c, 0x2b,
    0x95, 0x3d, 0x80, 0xa1, 0x37, 0x3b, 0xc5, 0xdc, 0x9e, 0x3e,
    0xc6, 0xc7, 0xe0, 0x3e, 0x6e, 0xcc, 0x86, 0xbe, 0x5a, 0x71,
    0x76, 0x3e, 0x75, 0x37, 0x46, 0xbe, 0x6f, 0x1b, 0xb6, 0xbe,
    0x57, 0xef, 0x8d, 0x3e, 0xbf, 0x63, 0xfa, 0xbd, 0x3e, 0x25,
    0x1c, 0xbe, 0x57, 0x49, 0xab, 0x3e, 0xe6, 0x56, 0x36, 0x3e,
    0x64, 0x4d, 0x8a, 0xbe, 0xb7, 0x42, 0xda, 0xbe, 0xb9, 0x1c,
    0xbf, 0xbe, 0xa1, 0xb9, 0x87, 0x3e, 0x46, 0x69, 0x16, 0xbe,
    0x4c, 0x57, 0xcf, 0x3d, 0xd7, 0xd2, 0x8c, 0x3e, 0xb3, 0x59,
    0xa6, 0x3e, 0x1e, 0x44, 0x6d, 0x3e, 0xe8, 0x1a, 0xe7, 0xbd,
    0x6d, 0x3a, 0x44, 0xbe, 0x71, 0x9f, 0xa0, 0x3e, 0x77, 0x5b,
    0xd3, 0xbe, 0x10, 0xb6, 0xdb, 0xbe, 0xb6, 0x54, 0x46, 0x3e,
    0x88, 0x7e, 0x2b, 0xbe, 0x09, 0x08, 0x7b, 0xbe, 0xd0, 0x39,
    0xa4, 0xbe, 0xcb, 0xf7, 0xb1, 0x3e, 0x4e, 0x03, 0xdd, 0xbe,
    0x0e, 0x3d, 0x3a, 0x3e, 0x9c, 0xbd, 0xd5, 0xbe, 0x7e, 0x7c,
    0xca, 0xbe, 0x2d, 0xc6, 0xa4, 0x3e, 0x90, 0x62, 0x58, 0x3d,
    0xae, 0x33, 0xa1, 0xbe, 0xa4, 0x03, 0xc0, 0xbe, 0x26, 0x00,
    0x0a, 0x3e, 0x18, 0xe5, 0xda, 0xbd, 0x24, 0xe3, 0xb3, 0x3e,
    0xce, 0xc6, 0x3d, 0x3e, 0xea, 0x13, 0x5b, 0x3d, 0x5b, 0xfb,
    0x82, 0xbf, 0x9e, 0xd1, 0xb5, 0x3e, 0x0a, 0xea, 0x7e, 0x3e,
    0x33, 0xcf, 0xa9, 0x3e, 0x96, 0x88, 0x5a, 0x3e, 0xf6, 0x3c,
    0xcd, 0xbe, 0x4c, 0x66, 0x90, 0xbf, 0x6b, 0x7f, 0xbe, 0xbe,
    0x30, 0xb2, 0x0f, 0xbe, 0x86, 0xdd, 0x70, 0xbe, 0x0e, 0xe8,
    0x63, 0x3e, 0x0c, 0xf4, 0x3b, 0x3d, 0xe7, 0xb6, 0x2e, 0x3e,
    0xd7, 0x1a, 0x46, 0x3e, 0x56, 0xdd, 0x8e, 0xbe, 0xce, 0x37,
    0xbe, 0xbd, 0x99, 0xe6, 0x7e, 0xbe, 0xd9, 0x41, 0x66, 0xbe,
    0x66, 0x30, 0x45, 0x3e, 0x01, 0x6d, 0xd6, 0xbe, 0xee, 0x6c,
    0x96, 0xbe, 0xd0, 0xd2, 0x52, 0x3d, 0x4e, 0x75, 0xb1, 0x3e,
    0x8f, 0x9e, 0xdb, 0x3e, 0x13, 0x0c, 0x6a, 0xbe, 0x9d, 0x1a,
    0x56, 0xbe, 0xe4, 0x6e, 0x4f, 0xbe, 0x71, 0xb1, 0x3f, 0xbe,
    0x9e, 0xe9, 0x2a, 0xbe, 0xe3, 0x87, 0x3c, 0xbe, 0x75, 0xff,
    0xb1, 0x3e, 0x27, 0xfc, 0x19, 0xbd, 0x44, 0x47, 0x34, 0xbe,
    0xa0, 0x79, 0x48, 0x3e, 0xb6, 0x08, 0xb5, 0xbe, 0xe5, 0x1c,
    0xd3, 0x3e, 0x6c, 0x36, 0xcb, 0xbd, 0x56, 0xda, 0x3a, 0x3e,
    0x45, 0xf2, 0xc3, 0x3e, 0x28, 0x94, 0x1e, 0xbe, 0x86, 0x53,
    0x5d, 0x3e, 0xee, 0x12, 0xb5, 0xbe, 0x6f, 0xd5, 0x45, 0xbe,
    0x79, 0xa5, 0x68, 0x3e, 0x86, 0x07, 0xae, 0x3d, 0xeb, 0xa9,
    0x43, 0xbe, 0x52, 0x7f, 0x07, 0xbe, 0xfa, 0x08, 0x6c, 0x3e,
    0x44, 0x72, 0xef, 0x3e, 0x0d, 0x2c, 0xf3, 0xbe, 0x50, 0x51,
    0xf8, 0x3c, 0x20, 0x94, 0x16, 0xbc, 0xa0, 0xbd, 0xa7, 0xbe,
    0x12, 0x4d, 0xef, 0xbd, 0xa1, 0xd2, 0xec, 0x3e, 0x80, 0x1e,
    0x9a, 0x3b, 0xc6, 0x55, 0xa8, 0xbe, 0x41, 0x12, 0x5f, 0xbe,
    0x14, 0xd7, 0x36, 0xbe, 0xd5, 0xc7, 0xc2, 0x3e, 0xbe, 0xe2,
    0x8d, 0x3e, 0x65, 0xb9, 0x8e, 0xbe, 0x8f, 0xae, 0x8a, 0x3e,
    0x79, 0x6d, 0x71, 0xbe, 0x2e, 0xe9, 0x29, 0x3e, 0x88, 0x00,
    0xf8, 0xbd, 0x8c, 0x64, 0xcb, 0x3d, 0xd9, 0x79, 0xb7, 0x3e,
    0x8a, 0xa7, 0xcd, 0xbe, 0x4d, 0x84, 0xa1, 0xbe, 0x44, 0x8f,
    0xb9, 0xbe, 0xe3, 0x13, 0x75, 0xbe, 0x94, 0xa1, 0xe4, 0x3d,
    0x9d, 0xe7, 0xb9, 0xbe, 0xfc, 0x31, 0xbd, 0xbd, 0x67, 0xf2,
    0xb2, 0xbe, 0xc1, 0x50, 0x93, 0xbe, 0x05, 0xa8, 0x13, 0x3e,
    0x87, 0x78, 0x76, 0xbe, 0x83, 0x07, 0x04, 0xbe, 0x58, 0xb6,
    0xac, 0x3e, 0xdf, 0x8b, 0x37, 0xbe, 0x35, 0x21, 0x84, 0xbe,
    0x4c, 0xa8, 0xc3, 0x3d, 0xa0, 0x6b, 0xe3, 0xbc, 0x10, 0x80,
    0xb2, 0xbc, 0x8b, 0x92, 0x07, 0x3e, 0xf8, 0xda, 0x0f, 0xbd,
    0xb3, 0x77, 0xa6, 0x3e, 0x74, 0xe4, 0x84, 0x3d, 0xe5, 0x1f,
    0xae, 0x3e, 0x94, 0x65, 0xdf, 0xbd, 0xf8, 0x0e, 0xaf, 0xbe,
    0xd3, 0x04, 0x83, 0xbe, 0xf7, 0xc1, 0xd0, 0x3e, 0x99, 0x00,
    0xc6, 0xbe, 0x19, 0x6c, 0xd7, 0x39, 0x1a, 0xf8, 0x48, 0x3e,
    0xf1, 0xcf, 0xdc, 0x3e, 0x88, 0x93, 0x55, 0xbd, 0x94, 0x41,
    0xb2, 0xbd, 0xc1, 0x74, 0xcc, 0xbe, 0x87, 0x48, 0x9d, 0x3d,
    0x71, 0xec, 0xd0, 0x3e, 0x9e, 0x34, 0xb1, 0xbe, 0x02, 0x32,
    0x3a, 0x3e, 0x36, 0x52, 0x27, 0x3e, 0x84, 0x57, 0x39, 0xbf,
    0x53, 0xff, 0xca, 0xbe, 0x86, 0x8d, 0x6f, 0x3e, 0xfc, 0xef,
    0xf5, 0x3d, 0xe5, 0x87, 0xb5, 0xbe, 0x7f, 0xa5, 0xc7, 0xbc,
    0x1b, 0x35, 0xa3, 0x3e, 0xca, 0xc0, 0x17, 0x3e, 0x6a, 0x59,
    0x1d, 0x3e, 0xc2, 0x22, 0x18, 0x3e, 0x88, 0xf2, 0xab, 0xbe,
    0x9b, 0x4f, 0x83, 0x3e, 0xba, 0x21, 0x4d, 0x3e, 0x67, 0xe8,
    0x81, 0x3e, 0x1e, 0x1a, 0x67, 0x3e, 0x4f, 0xc0, 0xbf, 0x3e,
    0xc9, 0xd3, 0x69, 0x3e, 0xd9, 0x27, 0x95, 0xbe, 0x6c, 0xce,
    0xf3, 0xbd, 0xc6, 0xba, 0xb2, 0xbe, 0xff, 0xce, 0xdb, 0xbe,
    0x14, 0xb9, 0xee, 0xbd, 0x3f, 0x5b, 0x6e, 0x3d, 0xba, 0x16,
    0x7e, 0x3e, 0x2c, 0x0f, 0xa8, 0x3d, 0x42, 0xba, 0x2c, 0xbe,
    0xbe, 0x14, 0x22, 0x3e, 0xec, 0x99, 0x86, 0xbe, 0x86, 0xad,
    0x51, 0x3e, 0x15, 0xfc, 0xdc, 0x3e, 0x67, 0x64, 0x91, 0x3e,
    0xde, 0xae, 0x2f, 0x3e, 0xdd, 0x0f, 0x22, 0xbf, 0x19, 0x77,
    0xa6, 0xbe, 0xc0, 0x42, 0xf1, 0x3d, 0xdf, 0x7a, 0x92, 0xbe,
    0xc4, 0x3e, 0x1e, 0x3e, 0x13, 0x3b, 0x4d, 0x3d, 0xae, 0x74,
    0x1a, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x8c, 0x69, 0xc6, 0x3e, 0xa4, 0x40, 0x7a, 0xbc, 0xc7, 0x21,
    0x7c, 0xbe, 0xa6, 0x96, 0x9b, 0xbf, 0x00, 0x00, 0x00, 0x00,
    0x04, 0xa5, 0x23, 0xbc, 0xbb, 0x63, 0x52, 0x3e, 0xa5, 0x07,
    0xdb, 0x3d, 0x4e, 0x87, 0xdb, 0x3e, 0x8f, 0xaf, 0x18, 0xbe,
    0x24, 0x9d, 0x18, 0x3f, 0x4e, 0x64, 0xa8, 0xbf, 0x7c, 0x85,
    0xc9, 0xbd, 0xd9, 0x9a, 0xbb, 0xbf, 0x68, 0x36, 0x99,
    0x3d, 0x18, 0x97, 0xb4, 0xbd, 0x08, 0xcc, 0xaa, 0x3f,
    0x90, 0xe6, 0xf1, 0xbe, 0x31, 0x17, 0x57, 0x3e, 0x93,
    0xd9, 0xa9, 0x3f, 0x20, 0x87, 0xf5, 0xbc, 0x2a, 0x43,
    0xbd, 0xbd, 0x38, 0x4a, 0x69, 0xbf, 0x61, 0x9e, 0x18,
    0xbf, 0xbe, 0x64, 0x35, 0xbf, 0x1a, 0x8f, 0x90, 0xbe
  };

  return AI_HANDLE_PTR(s_sine_model_weights);

}

