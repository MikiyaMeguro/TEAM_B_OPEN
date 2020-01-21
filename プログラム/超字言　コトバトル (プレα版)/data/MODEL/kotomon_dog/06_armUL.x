xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 161;
 6.97295;2.05501;-0.00194;,
 5.69472;2.06342;0.01699;,
 5.56374;1.82523;0.91571;,
 6.70169;1.81777;0.89886;,
 8.64299;-0.10936;0.90039;,
 8.54247;-0.88950;0.81289;,
 8.62324;-0.95807;-0.05661;,
 8.62906;-0.09731;-0.04574;,
 6.67672;-1.87523;0.85217;,
 5.53876;-1.86775;0.86904;,
 5.66668;-2.08490;-0.03544;,
 6.94494;-2.09328;-0.05438;,
 0.17695;-0.93462;1.03807;,
 0.18477;-0.06666;1.18167;,
 0.16854;-0.05263;0.08003;,
 0.16177;-1.05488;0.06737;,
 6.98889;-0.12456;2.04054;,
 5.71063;-0.11617;2.05946;,
 5.61127;-0.97176;1.88284;,
 6.78652;-0.97950;1.86541;,
 6.73034;-0.93091;-1.94829;,
 5.55510;-0.92317;-1.93088;,
 5.64953;-0.06334;-2.08850;,
 6.92780;-0.07174;-2.10746;,
 1.39707;1.85261;0.97744;,
 2.90374;1.84270;0.95511;,
 2.88527;2.08188;0.05861;,
 1.38006;2.09177;0.08091;,
 1.25884;-0.94316;1.94731;,
 2.84009;-0.95355;1.92387;,
 2.84003;-0.09731;2.10198;,
 1.27063;-0.08700;2.12524;,
 1.28722;-2.05610;0.02944;,
 2.82563;-2.06621;0.00664;,
 2.86441;-1.85016;0.90865;,
 1.34259;-1.84017;0.93119;,
 2.79858;-0.90508;-1.89005;,
 1.23268;-0.89476;-1.86687;,
 1.27131;-0.03455;-2.02366;,
 2.80909;-0.04467;-2.04645;,
 0.54278;1.87722;0.09005;,
 0.55253;1.63140;0.85866;,
 0.55700;-0.07116;1.91581;,
 0.54903;-0.76224;1.68433;,
 0.51770;-1.83097;0.04317;,
 0.53067;-1.60483;0.81774;,
 0.14320;-0.59539;-1.30163;,
 0.14437;-0.01374;-1.48021;,
 8.25733;-1.62006;-0.06868;,
 8.10160;-1.48763;0.66032;,
 8.29110;-0.10867;1.53957;,
 8.12673;-0.76055;1.40100;,
 8.27886;1.56460;-0.02842;,
 8.12121;1.41593;0.69703;,
 8.08373;-0.72335;-1.51812;,
 8.24418;-0.06812;-1.64481;,
 0.14920;-0.03592;-1.23375;,
 0.14581;-0.88266;-1.08691;,
 0.50603;-1.53899;-0.87461;,
 1.32144;-1.77237;-1.04168;,
 2.84012;-1.78235;-1.06418;,
 5.48324;-1.79971;-1.10334;,
 6.59484;-1.80701;-1.11980;,
 8.04693;-1.44081;-0.92864;,
 8.49694;-0.85035;-1.08827;,
 8.61247;-0.08293;-1.17400;,
 8.06620;1.41001;-0.89261;,
 6.61926;1.80052;-1.07420;,
 5.50761;1.80782;-1.05774;,
 2.87567;1.82512;-1.01875;,
 1.36872;1.83503;-0.99644;,
 0.52730;1.60870;-0.83483;,
 8.49887;0.82266;-1.05902;,
 8.63588;0.91055;-0.03301;,
 8.54592;0.81454;0.82783;,
 8.12283;0.67214;1.40804;,
 6.78251;0.89848;1.87518;,
 5.61601;0.90615;1.89246;,
 2.85328;0.92431;1.93340;,
 1.27102;0.93471;1.95684;,
 0.55907;0.76361;1.68472;,
 0.18960;0.96484;1.05082;,
 0.17648;1.12089;0.09487;,
 0.15849;0.96461;-1.05022;,
 0.51157;0.80470;-1.53994;,
 1.24258;0.98272;-1.82888;,
 2.81087;0.97243;-1.85212;,
 5.56025;0.95436;-1.89282;,
 6.72678;0.94670;-1.91011;,
 8.08018;0.70904;-1.48855;,
 4.33647;-0.10714;2.07981;,
 4.34784;-0.96345;1.90155;,
 4.36199;0.91439;1.91105;,
 4.32053;2.07244;0.03736;,
 4.34041;1.83327;0.93384;,
 4.31260;1.81568;-1.04004;,
 4.27538;-0.05430;-2.06816;,
 4.30624;0.96259;-1.87425;,
 4.29166;-0.91490;-1.91218;,
 4.28821;-1.79186;-1.08562;,
 4.29250;-2.07587;-0.01510;,
 4.31544;-1.85970;0.88715;,
 6.11873;1.39013;1.41986;,
 7.98937;1.29157;1.30369;,
 5.24264;1.39588;1.43284;,
 4.30083;1.40206;1.44680;,
 3.06663;1.41019;1.46508;,
 1.77224;1.41869;1.48426;,
 0.56072;1.42584;1.50139;,
 0.54278;1.87722;0.09005;,
 0.55253;1.63140;0.85866;,
 0.52730;1.60870;-0.83483;,
 0.51885;1.46205;-1.33993;,
 1.73035;1.45490;-1.35868;,
 3.02474;1.44639;-1.37786;,
 4.25894;1.43828;-1.39614;,
 5.20074;1.43209;-1.41010;,
 6.07689;1.42633;-1.42306;,
 7.95008;1.32557;-1.36458;,
 0.54150;-1.41572;1.46546;,
 1.75302;-1.42448;1.44832;,
 3.04742;-1.43296;1.42914;,
 4.28159;-1.44109;1.41084;,
 5.37964;-1.62017;1.56215;,
 6.36030;-1.62662;1.54763;,
 7.97133;-1.37690;1.26998;,
 6.05763;-1.41682;-1.45900;,
 7.93202;-1.34293;-1.39828;,
 5.18155;-1.41107;-1.44603;,
 4.23972;-1.40489;-1.43208;,
 3.00553;-1.39676;-1.41380;,
 1.71115;-1.38825;-1.39460;,
 0.49965;-1.37952;-1.37586;,
 0.51157;0.80470;-1.53994;,
 0.51885;1.46205;-1.33993;,
 0.14437;-0.01374;-1.48021;,
 0.14320;-0.59539;-1.30163;,
 0.49965;-1.37952;-1.37586;,
 1.71115;-1.38825;-1.39460;,
 3.00553;-1.39676;-1.41380;,
 4.23972;-1.40489;-1.43208;,
 5.18155;-1.41107;-1.44603;,
 6.05763;-1.41682;-1.45900;,
 7.93202;-1.34293;-1.39828;,
 8.08373;-0.72335;-1.51812;,
 8.24418;-0.06812;-1.64481;,
 8.08018;0.70904;-1.48855;,
 3.04742;-1.43296;1.42914;,
 4.28159;-1.44109;1.41084;,
 1.75302;-1.42448;1.44832;,
 0.54150;-1.41572;1.46546;,
 0.54903;-0.76224;1.68433;,
 0.55700;-0.07116;1.91581;,
 0.55907;0.76361;1.68472;,
 0.56072;1.42584;1.50139;,
 8.12283;0.67214;1.40804;,
 8.29110;-0.10867;1.53957;,
 8.12673;-0.76055;1.40100;,
 7.97133;-1.37690;1.26998;,
 6.36030;-1.62662;1.54763;,
 5.37964;-1.62017;1.56215;;
 
 128;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;27,40,41,24;,
 4;31,42,43,28;,
 4;44,32,35,45;,
 4;37,46,47,38;,
 4;11,48,49,8;,
 4;50,16,19,51;,
 4;52,0,3,53;,
 4;54,20,23,55;,
 4;56,57,15,14;,
 4;58,59,32,44;,
 4;59,60,33,32;,
 4;61,62,11,10;,
 4;62,63,48,11;,
 4;64,65,7,6;,
 4;66,67,0,52;,
 4;67,68,1,0;,
 4;69,70,27,26;,
 4;70,71,40,27;,
 4;65,72,73,7;,
 4;74,4,7,73;,
 4;75,76,16,50;,
 4;76,77,17,16;,
 4;78,79,31,30;,
 4;79,80,42,31;,
 4;13,81,82,14;,
 4;83,56,14,82;,
 4;38,47,84,85;,
 4;85,86,39,38;,
 4;23,22,87,88;,
 4;55,23,88,89;,
 4;90,30,29,91;,
 4;92,78,30,90;,
 4;93,26,25,94;,
 4;95,69,26,93;,
 4;96,39,86,97;,
 4;98,36,39,96;,
 4;60,99,100,33;,
 4;101,34,33,100;,
 4;68,95,93,1;,
 4;94,2,1,93;,
 4;77,92,90,17;,
 4;91,18,17,90;,
 4;100,10,9,101;,
 4;99,61,10,100;,
 4;21,98,96,22;,
 4;97,87,22,96;,
 4;72,66,52,73;,
 4;53,74,73,52;,
 4;102,76,75,103;,
 4;104,77,76,102;,
 4;105,92,77,104;,
 4;106,78,92,105;,
 4;107,79,78,106;,
 4;108,80,79,107;,
 4;109,82,81,110;,
 4;111,83,82,109;,
 4;85,84,112,113;,
 4;114,86,85,113;,
 4;97,86,114,115;,
 4;116,87,97,115;,
 4;88,87,116,117;,
 4;89,88,117,118;,
 4;57,58,44,15;,
 4;45,12,15,44;,
 4;28,43,119,120;,
 4;121,29,28,120;,
 4;91,29,121,122;,
 4;123,18,91,122;,
 4;19,18,123,124;,
 4;51,19,124,125;,
 4;48,6,5,49;,
 4;63,64,6,48;,
 4;126,20,54,127;,
 4;128,21,20,126;,
 4;129,98,21,128;,
 4;130,36,98,129;,
 4;131,37,36,130;,
 4;132,46,37,131;,
 4;133,83,111,134;,
 4;135,56,83,133;,
 4;136,57,56,135;,
 4;137,58,57,136;,
 4;138,59,58,137;,
 4;139,60,59,138;,
 4;140,99,60,139;,
 4;141,61,99,140;,
 4;142,62,61,141;,
 4;143,63,62,142;,
 4;144,64,63,143;,
 4;145,65,64,144;,
 4;146,72,65,145;,
 4;118,66,72,146;,
 4;117,67,66,118;,
 4;116,68,67,117;,
 4;115,95,68,116;,
 4;114,69,95,115;,
 4;113,70,69,114;,
 4;112,71,70,113;,
 4;147,34,101,148;,
 4;35,34,147,149;,
 4;45,35,149,150;,
 4;151,12,45,150;,
 4;152,13,12,151;,
 4;153,81,13,152;,
 4;110,81,153,154;,
 4;24,41,108,107;,
 4;106,25,24,107;,
 4;94,25,106,105;,
 4;104,2,94,105;,
 4;3,2,104,102;,
 4;53,3,102,103;,
 4;155,74,53,103;,
 4;156,4,74,155;,
 4;157,5,4,156;,
 4;49,5,157,158;,
 4;8,49,158,159;,
 4;160,9,8,159;,
 4;101,9,160,148;;
 
 MeshMaterialList {
  1;
  128;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\dog_color.jpg";
   }
  }
 }
 MeshNormals {
  131;
  -0.443857;0.632116;-0.635154;,
  -0.448928;0.632258;0.631437;,
  0.387857;0.642296;-0.661077;,
  0.427324;0.643144;0.635421;,
  0.376904;-0.639532;-0.670031;,
  0.471859;-0.655325;0.589829;,
  -0.474894;-0.625450;-0.619103;,
  -0.456717;-0.648364;0.609126;,
  -0.006025;0.697758;-0.716308;,
  0.014935;0.728708;0.684662;,
  -0.050186;-0.747651;0.662193;,
  -0.015299;-0.683633;-0.729666;,
  -0.099418;0.699909;-0.707279;,
  -0.079119;0.719432;0.690042;,
  -0.089498;-0.740471;0.666103;,
  -0.121580;-0.675178;-0.727567;,
  0.085466;-0.687523;-0.721116;,
  0.149431;-0.739317;0.656568;,
  0.115976;0.718604;0.685681;,
  0.094442;0.698954;-0.708903;,
  -0.631613;0.775037;0.019592;,
  -0.650248;-0.759722;0.000266;,
  -0.154272;-0.987981;-0.009642;,
  -0.006753;-0.999905;-0.012021;,
  0.156472;-0.987583;-0.014018;,
  0.609131;-0.792859;-0.018272;,
  0.618698;0.785627;0.001707;,
  0.169804;0.985417;0.010916;,
  0.006765;0.999889;0.013257;,
  -0.133174;0.990975;0.015293;,
  0.555055;-0.004264;-0.831803;,
  0.999849;-0.009225;-0.014726;,
  0.630768;-0.024898;0.775572;,
  0.190108;-0.023563;0.981480;,
  0.014671;-0.020866;0.999675;,
  -0.162795;-0.020746;0.986442;,
  -0.650030;-0.013320;0.759791;,
  -0.999869;0.006569;0.014807;,
  -0.806048;0.069056;-0.587808;,
  -0.236914;-0.011742;-0.971460;,
  -0.014774;0.004610;-0.999880;,
  0.161109;0.001506;-0.986935;,
  0.004877;-0.749843;0.661598;,
  0.014672;-0.020871;0.999674;,
  0.014933;0.728711;0.684658;,
  0.006768;0.999889;0.013259;,
  -0.006025;0.697761;-0.716305;,
  -0.014780;0.004606;-0.999880;,
  -0.015309;-0.683630;-0.729668;,
  -0.006751;-0.999905;-0.012020;,
  -0.006022;0.697756;-0.716310;,
  0.006765;0.999889;0.013252;,
  0.014930;0.728703;0.684667;,
  0.014672;-0.020862;0.999675;,
  -0.052226;-0.746704;0.663103;,
  -0.006745;-0.999905;-0.012023;,
  -0.015294;-0.683628;-0.729671;,
  -0.014782;0.004610;-0.999880;,
  0.517213;0.385900;-0.763918;,
  0.951139;0.308609;-0.009785;,
  0.578394;0.364180;0.729954;,
  0.158713;0.411557;0.897458;,
  0.016189;0.446366;0.894704;,
  0.016191;0.446364;0.894705;,
  0.016188;0.446361;0.894707;,
  -0.129442;0.403767;0.905658;,
  -0.621330;0.311994;0.718755;,
  -0.969311;0.245223;0.017397;,
  -0.653846;0.362908;-0.663915;,
  -0.170932;0.408326;-0.896690;,
  -0.009999;0.469006;-0.883139;,
  -0.009994;0.469001;-0.883141;,
  -0.010000;0.469002;-0.883140;,
  0.132371;0.434332;-0.890974;,
  -0.570804;-0.388710;-0.723248;,
  -0.973123;-0.230003;0.011391;,
  -0.624216;-0.335983;0.705316;,
  -0.134357;-0.440216;0.887783;,
  0.009822;-0.481390;0.876451;,
  -0.017802;-0.440602;0.897526;,
  -0.016275;-0.363711;0.931370;,
  0.169940;-0.341099;0.924539;,
  0.585929;-0.370921;0.720490;,
  0.946333;-0.322706;-0.017775;,
  0.510307;-0.391634;-0.765643;,
  0.128041;-0.429386;-0.893998;,
  -0.016170;-0.458898;-0.888342;,
  -0.016170;-0.458898;-0.888342;,
  -0.016180;-0.458905;-0.888338;,
  -0.201397;-0.400521;-0.893880;,
  -0.594178;0.727311;-0.343469;,
  -0.935448;0.294344;-0.195703;,
  -0.995009;0.077942;-0.062307;,
  -0.969798;-0.225837;-0.092136;,
  -0.607073;-0.722651;-0.330510;,
  -0.127950;-0.874059;-0.468668;,
  -0.013341;-0.852860;-0.521969;,
  -0.013337;-0.852862;-0.521966;,
  -0.013331;-0.852859;-0.521972;,
  0.114162;-0.869654;-0.480280;,
  0.527731;-0.732815;-0.429515;,
  0.850001;-0.353967;-0.390136;,
  0.921355;-0.008122;-0.388637;,
  0.856531;0.341862;-0.386633;,
  0.539021;0.733195;-0.414585;,
  0.125988;0.879896;-0.458160;,
  -0.001718;0.865886;-0.500239;,
  -0.001721;0.865888;-0.500235;,
  -0.001718;0.865887;-0.500236;,
  -0.111339;0.888507;-0.445151;,
  -0.027669;-0.916318;0.399494;,
  0.000607;-0.898313;0.439356;,
  -0.111669;-0.908217;0.403327;,
  -0.610231;-0.721236;0.327775;,
  -0.940497;-0.232770;0.247554;,
  -0.966390;0.000760;0.257077;,
  -0.937439;0.236149;0.255817;,
  -0.596005;0.723843;0.347606;,
  -0.094343;0.900350;0.424817;,
  0.012671;0.886843;0.461897;,
  0.012670;0.886840;0.461903;,
  0.012666;0.886840;0.461904;,
  0.138924;0.891898;0.430369;,
  0.564772;0.727904;0.388831;,
  0.890089;0.316454;0.328021;,
  0.953136;-0.016280;0.302103;,
  0.884244;-0.345570;0.314155;,
  0.567539;-0.755714;0.326795;,
  0.139982;-0.945543;0.293861;,
  -0.028687;-0.946214;0.322267;,
  -0.999734;0.008108;0.021589;;
  128;
  4;27,51,121,122;,
  4;125,126,83,31;,
  4;128,129,55,24;,
  4;114,115,37,75;,
  4;33,53,80,81;,
  4;85,86,57,41;,
  4;118,119,45,29;,
  4;77,78,43,35;,
  4;22,49,111,112;,
  4;88,89,39,47;,
  4;29,20,117,118;,
  4;35,36,76,77;,
  4;21,22,112,113;,
  4;89,74,38,39;,
  4;24,25,127,128;,
  4;32,33,81,82;,
  4;26,27,122,123;,
  4;84,85,41,30;,
  4;92,93,75,37;,
  4;94,95,22,21;,
  4;95,96,49,22;,
  4;98,99,24,55;,
  4;99,100,25,24;,
  4;101,102,31,83;,
  4;104,105,27,26;,
  4;105,106,51,27;,
  4;108,109,29,45;,
  4;109,90,20,29;,
  4;102,103,59,31;,
  4;124,125,31,59;,
  4;60,61,33,32;,
  4;61,62,53,33;,
  4;64,65,35,43;,
  4;65,66,36,35;,
  4;115,116,67,37;,
  4;91,92,37,67;,
  4;39,38,68,69;,
  4;69,70,47,39;,
  4;41,57,72,73;,
  4;30,41,73,58;,
  4;34,43,78,79;,
  4;63,64,43,34;,
  4;28,45,119,120;,
  4;107,108,45,28;,
  4;40,47,70,71;,
  4;87,88,47,40;,
  4;96,97,23,49;,
  4;110,111,49,23;,
  4;106,107,28,51;,
  4;120,121,51,28;,
  4;62,63,34,53;,
  4;79,80,53,34;,
  4;23,55,129,110;,
  4;97,98,55,23;,
  4;86,87,40,57;,
  4;71,72,57,40;,
  4;103,104,26,59;,
  4;123,124,59,26;,
  4;18,61,60,3;,
  4;52,62,61,18;,
  4;9,63,62,52;,
  4;44,64,63,9;,
  4;13,65,64,44;,
  4;1,66,65,13;,
  4;20,67,116,117;,
  4;90,91,67,20;,
  4;69,68,0,12;,
  4;46,70,69,12;,
  4;71,70,46,8;,
  4;50,72,71,8;,
  4;73,72,50,19;,
  4;58,73,19,2;,
  4;93,94,21,75;,
  4;113,114,75,21;,
  4;77,76,7,14;,
  4;42,78,77,14;,
  4;79,78,42,10;,
  4;54,80,79,10;,
  4;81,80,54,17;,
  4;82,81,17,5;,
  4;25,83,126,127;,
  4;100,101,83,25;,
  4;16,85,84,4;,
  4;56,86,85,16;,
  4;11,87,86,56;,
  4;48,88,87,11;,
  4;15,89,88,48;,
  4;6,74,89,15;,
  4;68,91,90,0;,
  4;38,92,91,68;,
  4;130,93,92,38;,
  4;6,94,93,74;,
  4;15,95,94,6;,
  4;48,96,95,15;,
  4;11,97,96,48;,
  4;56,98,97,11;,
  4;16,99,98,56;,
  4;4,100,99,16;,
  4;84,101,100,4;,
  4;30,102,101,84;,
  4;58,103,102,30;,
  4;2,104,103,58;,
  4;19,105,104,2;,
  4;50,106,105,19;,
  4;8,107,106,50;,
  4;46,108,107,8;,
  4;12,109,108,46;,
  4;0,90,109,12;,
  4;42,111,110,10;,
  4;112,111,42,14;,
  4;113,112,14,7;,
  4;76,114,113,7;,
  4;36,115,114,76;,
  4;66,116,115,36;,
  4;117,116,66,1;,
  4;118,117,1,13;,
  4;44,119,118,13;,
  4;120,119,44,9;,
  4;52,121,120,9;,
  4;122,121,52,18;,
  4;123,122,18,3;,
  4;60,124,123,3;,
  4;32,125,124,60;,
  4;82,126,125,32;,
  4;127,126,82,5;,
  4;128,127,5,17;,
  4;54,129,128,17;,
  4;110,129,54,10;;
 }
 MeshTextureCoords {
  161;
  0.500040;0.153970;,
  0.500040;0.158700;,
  0.510960;0.158700;,
  0.510960;0.153970;,
  0.510960;0.122060;,
  0.510960;0.112130;,
  0.500040;0.112130;,
  0.500040;0.122060;,
  0.510960;0.091690;,
  0.510960;0.086960;,
  0.500040;0.086960;,
  0.500040;0.091690;,
  0.510960;0.053190;,
  0.510960;0.043260;,
  0.500040;0.043260;,
  0.500040;0.053190;,
  0.540930;0.153970;,
  0.540930;0.158700;,
  0.550860;0.158700;,
  0.550860;0.153970;,
  0.449140;0.153970;,
  0.449140;0.158700;,
  0.459070;0.158700;,
  0.459070;0.153970;,
  0.510960;0.175990;,
  0.510960;0.169740;,
  0.500040;0.169740;,
  0.500040;0.175990;,
  0.550860;0.175990;,
  0.550860;0.169740;,
  0.540930;0.169740;,
  0.540930;0.175990;,
  0.500040;0.069670;,
  0.500040;0.075920;,
  0.510960;0.075920;,
  0.510960;0.069670;,
  0.449140;0.169740;,
  0.449140;0.175990;,
  0.459070;0.175990;,
  0.459070;0.169740;,
  0.500040;0.183080;,
  0.510960;0.183080;,
  0.540930;0.183080;,
  0.550860;0.183080;,
  0.500040;0.062580;,
  0.510960;0.062580;,
  0.449140;0.183080;,
  0.459070;0.183080;,
  0.500040;0.102750;,
  0.510960;0.102750;,
  0.540930;0.142910;,
  0.550860;0.142910;,
  0.500040;0.142910;,
  0.510960;0.142910;,
  0.449140;0.142910;,
  0.459070;0.142910;,
  0.487030;0.043260;,
  0.487030;0.053190;,
  0.487030;0.062580;,
  0.487030;0.069670;,
  0.487030;0.075920;,
  0.487030;0.086960;,
  0.487030;0.091690;,
  0.487030;0.102750;,
  0.487030;0.112130;,
  0.487030;0.122060;,
  0.487030;0.142910;,
  0.487030;0.153970;,
  0.487030;0.158700;,
  0.487030;0.169740;,
  0.487030;0.175990;,
  0.487030;0.183080;,
  0.487030;0.133690;,
  0.500040;0.133690;,
  0.510960;0.133690;,
  0.529300;0.142910;,
  0.529300;0.153970;,
  0.529300;0.158700;,
  0.529300;0.169740;,
  0.529300;0.175990;,
  0.529300;0.183080;,
  0.510960;0.031640;,
  0.500040;0.031640;,
  0.487030;0.031640;,
  0.470690;0.183080;,
  0.470690;0.175990;,
  0.470690;0.169740;,
  0.470690;0.158700;,
  0.470690;0.153970;,
  0.470690;0.142910;,
  0.540930;0.163780;,
  0.550860;0.163780;,
  0.529300;0.163780;,
  0.500040;0.163780;,
  0.510960;0.163780;,
  0.487030;0.163780;,
  0.459070;0.163780;,
  0.470690;0.163780;,
  0.449140;0.163780;,
  0.487030;0.081870;,
  0.500040;0.081870;,
  0.510960;0.081870;,
  0.520080;0.153970;,
  0.520080;0.142910;,
  0.520080;0.158700;,
  0.520080;0.163780;,
  0.520080;0.169740;,
  0.520080;0.175990;,
  0.520080;0.183080;,
  0.500040;0.022420;,
  0.510960;0.022420;,
  0.487030;0.022420;,
  0.479920;0.183080;,
  0.479920;0.175990;,
  0.479920;0.169740;,
  0.479920;0.163780;,
  0.479920;0.158700;,
  0.479920;0.153970;,
  0.479920;0.142910;,
  0.560250;0.183080;,
  0.560250;0.175990;,
  0.560250;0.169740;,
  0.560250;0.163780;,
  0.560250;0.158700;,
  0.560250;0.153970;,
  0.560250;0.142910;,
  0.439750;0.153970;,
  0.439750;0.142910;,
  0.439750;0.158700;,
  0.439750;0.163780;,
  0.439750;0.169740;,
  0.439750;0.175990;,
  0.439750;0.183080;,
  0.479920;0.031640;,
  0.479920;0.022420;,
  0.479920;0.043260;,
  0.479920;0.053190;,
  0.479920;0.062580;,
  0.479920;0.069670;,
  0.479920;0.075920;,
  0.479920;0.081870;,
  0.479920;0.086960;,
  0.479920;0.091690;,
  0.479920;0.102750;,
  0.479920;0.112130;,
  0.479920;0.122060;,
  0.479920;0.133690;,
  0.520080;0.075920;,
  0.520080;0.081870;,
  0.520080;0.069670;,
  0.520080;0.062580;,
  0.520080;0.053190;,
  0.520080;0.043260;,
  0.520080;0.031640;,
  0.520080;0.022420;,
  0.520080;0.133690;,
  0.520080;0.122060;,
  0.520080;0.112130;,
  0.520080;0.102750;,
  0.520080;0.091690;,
  0.520080;0.086960;;
 }
}
