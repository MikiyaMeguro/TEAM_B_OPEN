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
 -7.53624;1.30018;-0.05597;,
 -6.17267;1.54426;-0.02775;,
 -6.15763;1.55442;-0.82498;,
 -7.52406;1.30842;-0.70210;,
 -8.17254;-0.16128;-0.51704;,
 -8.18114;-0.24748;-0.08715;,
 -8.17834;0.19679;-0.08143;,
 -8.16870;0.20332;-0.59305;,
 -6.17454;-1.11473;-0.85931;,
 -6.18953;-1.12490;-0.06205;,
 -7.54993;-0.86294;-0.08381;,
 -7.53775;-0.85471;-0.72991;,
 -0.02994;-0.69418;0.05918;,
 -0.13009;-0.64209;-0.83870;,
 -0.00718;0.13057;-0.86648;,
 -0.02480;0.11866;0.06963;,
 -7.52302;0.19114;-1.14956;,
 -6.15635;0.17576;-1.37714;,
 -6.16072;-0.51650;-1.38604;,
 -7.52659;-0.36989;-1.15680;,
 -7.56729;-0.39745;1.00601;,
 -6.21096;-0.55049;1.28269;,
 -6.20656;0.14177;1.29159;,
 -7.56372;0.16359;1.01323;,
 -3.03109;1.94103;-1.00353;,
 -3.05063;1.92779;0.03506;,
 -2.05862;1.92127;0.05365;,
 -2.03907;1.93451;-0.98495;,
 -2.04311;-0.76337;-1.71588;,
 -3.03513;-0.75685;-1.73447;,
 -3.02941;0.14500;-1.72288;,
 -2.03741;0.13849;-1.70427;,
 -2.08061;-1.55594;0.00895;,
 -3.07265;-1.54944;-0.00964;,
 -3.05313;-1.53619;-1.04825;,
 -2.06111;-1.54271;-1.02967;,
 -3.10055;-0.80112;1.74220;,
 -2.10853;-0.80764;1.76081;,
 -2.10280;0.09419;1.77240;,
 -3.09485;0.10071;1.75381;,
 -0.41313;1.59747;0.08114;,
 -0.59662;1.54144;-0.70776;,
 -0.39572;0.13560;-1.36034;,
 -0.57935;-0.54285;-1.31179;,
 -0.43119;-1.25381;0.04448;,
 -0.61380;-1.17518;-0.74268;,
 -0.63071;-0.57760;1.41779;,
 -0.44941;0.09929;1.49050;,
 -7.89465;-0.55833;-0.08577;,
 -7.88754;-0.41794;-0.41336;,
 -7.87526;0.20107;-0.85362;,
 -7.87934;-0.08201;-0.73461;,
 -7.88476;1.00011;-0.06572;,
 -7.87945;0.86813;-0.39683;,
 -7.90407;-0.09873;0.57832;,
 -7.90459;0.18124;0.70458;,
 -0.04240;0.10672;1.00524;,
 -0.16326;-0.66511;0.95339;,
 -0.64242;-1.19548;0.82581;,
 -2.10018;-1.56917;1.04697;,
 -3.09216;-1.56265;1.02839;,
 -6.20453;-1.13504;0.73475;,
 -7.56208;-0.87116;0.56195;,
 -7.90000;-0.42698;0.24570;,
 -8.18874;-0.17264;0.34495;,
 -8.18795;0.19026;0.42993;,
 -7.89183;0.86038;0.26224;,
 -7.54839;1.29197;0.58977;,
 -6.18762;1.53412;0.76909;,
 -3.07017;1.91456;1.07310;,
 -2.07815;1.90805;1.09168;,
 -0.62519;1.52175;0.86076;,
 -8.18460;0.52280;0.36747;,
 -8.17579;0.59519;-0.07631;,
 -8.16785;0.53378;-0.52177;,
 -7.87551;0.46034;-0.74837;,
 -7.51985;0.69425;-1.14310;,
 -6.15242;0.79654;-1.36916;,
 -3.02430;0.95373;-1.71249;,
 -2.03229;0.94721;-1.69387;,
 -0.54085;0.74867;-1.30485;,
 -0.10082;0.82656;-0.82620;,
 -0.02019;0.84756;0.07901;,
 -0.13436;0.80369;0.97935;,
 -0.59260;0.71366;1.44521;,
 -2.09770;0.90292;1.78279;,
 -3.08970;0.90944;1.76421;,
 -6.20264;0.76255;1.29958;,
 -7.56054;0.66667;1.01970;,
 -7.90100;0.44309;0.60603;,
 -0.44941;0.09929;1.49050;,
 -0.59260;0.71366;1.44521;,
 -0.63071;-0.57760;1.41779;,
 -2.46666;-1.29780;1.46119;,
 -1.04758;-1.05967;1.24489;,
 -3.29867;-1.29233;1.44561;,
 -7.58698;-0.70492;0.82217;,
 -5.98679;-0.93072;1.06136;,
 -7.90363;-0.33794;0.47045;,
 -7.90459;0.18124;0.70458;,
 -7.90407;-0.09873;0.57832;,
 -7.90100;0.44309;0.60603;,
 -7.54057;1.10912;0.84616;,
 -7.89661;0.76562;0.48466;,
 -6.09660;1.40523;1.18681;,
 -2.44822;1.61859;1.49869;,
 -3.28020;1.62405;1.48312;,
 -1.03221;1.36648;1.27609;,
 -3.24379;-1.25518;-1.47032;,
 -2.19115;-1.40812;-1.60043;,
 -1.00190;-1.02878;-1.18090;,
 -0.39572;0.13560;-1.36034;,
 -0.57935;-0.54285;-1.31179;,
 -0.54085;0.74867;-1.30485;,
 -0.98655;1.39739;-1.14970;,
 -2.39332;1.65573;-1.41723;,
 -3.22535;1.66121;-1.43282;,
 -5.93048;1.33648;-1.14815;,
 -7.01060;1.04178;-0.87257;,
 -7.87588;0.77967;-0.61874;,
 -7.87526;0.20107;-0.85362;,
 -7.87551;0.46034;-0.74837;,
 -7.87934;-0.08201;-0.73461;,
 -7.88282;-0.32387;-0.63292;,
 -7.48512;-0.68536;-0.74871;,
 -5.94467;-0.90219;-1.17693;,
 -4.68968;1.59655;1.41897;,
 -4.70063;1.88104;1.01545;,
 -4.68162;1.89391;0.00403;,
 -4.66256;1.90679;-1.00793;,
 -4.63621;1.63273;-1.42216;,
 -4.65593;0.94482;-1.69867;,
 -4.66093;0.15684;-1.70880;,
 -4.66649;-0.72186;-1.72011;,
 -4.68404;-1.48122;-1.05152;,
 -4.65419;-1.20884;-1.45868;,
 -4.70305;-1.49411;-0.03953;,
 -4.72207;-1.50701;0.97187;,
 -4.70766;-1.24504;1.38243;,
 -4.73024;-0.76498;1.66739;,
 -4.74034;0.12175;1.52243;,
 -4.71970;0.90168;1.68882;,
 -0.59662;1.54144;-0.70776;,
 -0.98655;1.39739;-1.14970;,
 -0.41313;1.59747;0.08114;,
 -0.62519;1.52175;0.86076;,
 -1.03221;1.36648;1.27609;,
 -1.00190;-1.02878;-1.18090;,
 -2.19115;-1.40812;-1.60043;,
 -3.24379;-1.25518;-1.47032;,
 -4.65419;-1.20884;-1.45868;,
 -5.94467;-0.90219;-1.17693;,
 -7.48512;-0.68536;-0.74871;,
 -7.88282;-0.32387;-0.63292;,
 -7.58698;-0.70492;0.82217;,
 -7.90363;-0.33794;0.47045;,
 -5.98679;-0.93072;1.06136;,
 -4.70766;-1.24504;1.38243;,
 -3.29867;-1.29233;1.44561;,
 -2.46666;-1.29780;1.46119;,
 -1.04758;-1.05967;1.24489;;
 
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
 4;26,40,41,27;,
 4;31,42,43,28;,
 4;44,32,35,45;,
 4;37,46,47,38;,
 4;10,48,49,11;,
 4;50,16,19,51;,
 4;52,0,3,53;,
 4;54,20,23,55;,
 4;56,57,12,15;,
 4;58,59,32,44;,
 4;59,60,33,32;,
 4;9,61,62,10;,
 4;62,63,48,10;,
 4;5,64,65,6;,
 4;66,67,0,52;,
 4;67,68,1,0;,
 4;25,69,70,26;,
 4;70,71,40,26;,
 4;65,72,73,6;,
 4;73,74,7,6;,
 4;75,76,16,50;,
 4;76,77,17,16;,
 4;78,79,31,30;,
 4;79,80,42,31;,
 4;81,82,15,14;,
 4;82,83,56,15;,
 4;38,47,84,85;,
 4;85,86,39,38;,
 4;23,22,87,88;,
 4;55,23,88,89;,
 4;90,56,83,91;,
 4;92,57,56,90;,
 4;93,59,58,94;,
 4;95,60,59,93;,
 4;96,62,61,97;,
 4;98,63,62,96;,
 4;99,65,64,100;,
 4;101,72,65,99;,
 4;102,67,66,103;,
 4;104,68,67,102;,
 4;105,70,69,106;,
 4;107,71,70,105;,
 4;35,34,108,109;,
 4;45,35,109,110;,
 4;111,14,13,112;,
 4;113,81,14,111;,
 4;27,41,114,115;,
 4;116,24,27,115;,
 4;3,2,117,118;,
 4;53,3,118,119;,
 4;120,7,74,121;,
 4;122,4,7,120;,
 4;11,49,123,124;,
 4;125,8,11,124;,
 4;126,127,68,104;,
 4;1,68,127,128;,
 4;2,1,128,129;,
 4;117,2,129,130;,
 4;77,131,132,17;,
 4;133,18,17,132;,
 4;134,8,125,135;,
 4;136,9,8,134;,
 4;137,61,9,136;,
 4;97,61,137,138;,
 4;21,139,140,22;,
 4;141,87,22,140;,
 4;132,30,29,133;,
 4;131,78,30,132;,
 4;129,24,116,130;,
 4;128,25,24,129;,
 4;127,69,25,128;,
 4;106,69,127,126;,
 4;140,39,86,141;,
 4;139,36,39,140;,
 4;138,137,60,95;,
 4;33,60,137,136;,
 4;34,33,136,134;,
 4;108,34,134,135;,
 4;103,66,72,101;,
 4;73,72,66,52;,
 4;53,74,73,52;,
 4;121,74,53,119;,
 4;118,76,75,119;,
 4;117,77,76,118;,
 4;130,131,77,117;,
 4;116,78,131,130;,
 4;115,79,78,116;,
 4;114,80,79,115;,
 4;142,81,113,143;,
 4;144,82,81,142;,
 4;145,83,82,144;,
 4;91,83,145,146;,
 4;85,84,107,105;,
 4;106,86,85,105;,
 4;141,86,106,126;,
 4;104,87,141,126;,
 4;88,87,104,102;,
 4;89,88,102,103;,
 4;94,58,57,92;,
 4;12,57,58,44;,
 4;45,13,12,44;,
 4;112,13,45,110;,
 4;28,43,147,148;,
 4;149,29,28,148;,
 4;133,29,149,150;,
 4;151,18,133,150;,
 4;19,18,151,152;,
 4;51,19,152,153;,
 4;49,4,122,123;,
 4;48,5,4,49;,
 4;63,64,5,48;,
 4;100,64,63,98;,
 4;154,20,54,155;,
 4;156,21,20,154;,
 4;157,139,21,156;,
 4;158,36,139,157;,
 4;159,37,36,158;,
 4;160,46,37,159;;
 
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
  0.352572;0.565404;0.745661;,
  0.382022;0.580518;-0.719067;,
  -0.776954;0.420895;0.468178;,
  -0.642800;0.483400;-0.594250;,
  -0.776642;-0.454480;0.436206;,
  -0.690615;-0.442888;-0.571752;,
  0.329523;-0.655715;0.679303;,
  0.417112;-0.623936;-0.660849;,
  -0.148577;0.619962;0.770436;,
  -0.145519;0.618819;-0.771937;,
  -0.155996;-0.659869;-0.735009;,
  -0.182602;-0.683094;0.707135;,
  0.123638;0.605843;0.785918;,
  0.152996;0.621961;-0.767956;,
  0.145999;-0.676505;-0.721821;,
  0.119025;-0.689583;0.714359;,
  -0.581221;-0.572783;0.578015;,
  -0.513160;-0.487476;-0.706424;,
  -0.461024;0.522641;-0.717150;,
  -0.589151;0.521261;0.617405;,
  0.581716;0.813120;0.021023;,
  0.519095;-0.854715;-0.001407;,
  0.104436;-0.994473;-0.010779;,
  -0.137979;-0.990318;-0.015216;,
  -0.481137;-0.876408;-0.020434;,
  -0.708388;-0.705454;-0.022828;,
  -0.749187;0.662330;-0.006071;,
  -0.470009;0.882659;0.002211;,
  -0.125419;0.992051;0.010272;,
  0.117010;0.993021;0.014782;,
  -0.692711;-0.014052;0.721078;,
  -0.999803;0.006586;-0.018731;,
  -0.662663;0.004626;-0.748904;,
  -0.452940;0.010831;-0.891475;,
  -0.113054;0.013491;-0.993497;,
  0.126194;0.010564;-0.991949;,
  0.512265;0.002681;-0.858824;,
  0.999783;-0.009449;0.018567;,
  0.482310;-0.019443;0.875785;,
  0.088777;-0.014764;0.995942;,
  -0.143581;-0.017201;0.989489;,
  -0.486163;-0.011663;0.873790;,
  0.508361;0.742683;0.435880;,
  0.915289;-0.016196;0.402473;,
  0.455409;-0.797044;0.396639;,
  0.117159;-0.942881;0.311847;,
  -0.166019;-0.943860;0.285596;,
  -0.536588;-0.808471;0.241759;,
  -0.722095;-0.633752;0.277375;,
  -0.915871;-0.005698;0.401433;,
  -0.755677;0.587679;0.289113;,
  -0.529120;0.813650;0.240844;,
  -0.137011;0.952159;0.273167;,
  0.129317;0.929373;0.345750;,
  -0.154803;-0.937049;-0.313010;,
  0.119428;-0.967205;-0.224170;,
  0.485710;-0.803304;-0.344655;,
  0.928593;-0.006352;-0.371046;,
  0.525098;0.753443;-0.395722;,
  0.141695;0.938853;-0.313811;,
  -0.143112;0.943724;-0.298169;,
  -0.513200;0.714612;-0.475348;,
  -0.717254;0.563359;-0.410089;,
  -0.898751;0.004967;-0.438432;,
  -0.691566;-0.588493;-0.418823;,
  -0.532741;-0.690099;-0.489848;,
  -0.256238;0.615493;0.745326;,
  -0.227255;0.943919;0.239524;,
  -0.202489;0.979246;0.008657;,
  -0.256398;0.884658;-0.389410;,
  -0.261792;0.577126;-0.773557;,
  -0.190278;0.013830;-0.981633;,
  -0.255440;-0.599098;-0.758836;,
  -0.248767;-0.942661;-0.222495;,
  -0.214876;-0.976502;-0.016488;,
  -0.249225;-0.923574;0.291372;,
  -0.262471;-0.669909;0.694501;,
  -0.197672;-0.013996;0.980168;,
  -0.059230;-0.675167;-0.735283;,
  0.005153;0.012824;-0.999905;,
  0.001275;0.632527;-0.774537;,
  -0.004565;0.959862;-0.280435;,
  -0.007338;0.999894;0.012599;,
  -0.015606;0.951666;0.306737;,
  -0.028013;0.616536;0.786828;,
  -0.055637;-0.015214;0.998335;,
  -0.035507;-0.695546;0.717604;,
  -0.027498;-0.961766;0.272489;,
  -0.019995;-0.999714;-0.013114;,
  -0.042271;-0.969263;-0.242366;,
  -0.714832;0.279445;0.641035;,
  -0.841558;0.371131;0.392481;,
  -0.942046;0.335205;-0.013709;,
  -0.824653;0.382510;-0.416694;,
  -0.652800;0.383969;-0.653008;,
  -0.468749;0.371319;-0.801497;,
  -0.231259;0.274375;-0.933401;,
  -0.125861;0.206240;-0.970373;,
  0.004565;0.195118;-0.980769;,
  0.136266;0.227894;-0.964104;,
  0.473794;0.318211;-0.821134;,
  0.848675;0.346952;-0.399218;,
  0.953575;0.300385;0.021520;,
  0.833131;0.337378;0.438257;,
  0.443153;0.302357;0.843917;,
  0.100332;0.210953;0.972333;,
  -0.044595;0.153882;0.987082;,
  -0.146114;0.111156;0.983003;,
  -0.220853;0.116476;0.968327;,
  -0.520830;0.173113;0.835923;,
  0.432477;-0.391119;0.812397;,
  0.800517;-0.417100;0.430350;,
  0.927328;-0.374045;0.012405;,
  0.816267;-0.405067;-0.411861;,
  0.478572;-0.317434;-0.818660;,
  0.135107;-0.182463;-0.973886;,
  -0.022319;-0.188979;-0.981727;,
  -0.135331;-0.249217;-0.958945;,
  -0.237815;-0.312475;-0.919676;,
  -0.515789;-0.342764;-0.785159;,
  -0.672716;-0.350473;-0.651630;,
  -0.788567;-0.419006;-0.450108;,
  -0.921238;-0.388342;-0.022608;,
  -0.806628;-0.428781;0.406816;,
  -0.711466;-0.314139;0.628596;,
  -0.536688;-0.255779;0.804079;,
  -0.238988;-0.268492;0.933165;,
  -0.169378;-0.240869;0.955664;,
  -0.047604;-0.249291;0.967258;,
  0.105602;-0.307913;0.945536;,
  -0.209371;-0.410459;-0.887518;;
  128;
  4;27,68,69,61;,
  4;121,122,31,63;,
  4;73,74,24,65;,
  4;112,113,57,37;,
  4;33,71,118,119;,
  4;125,126,77,41;,
  4;81,82,29,59;,
  4;115,116,79,35;,
  4;22,88,89,55;,
  4;128,129,39,85;,
  4;29,20,58,59;,
  4;35,36,114,115;,
  4;21,22,55,56;,
  4;129,110,38,39;,
  4;24,25,64,65;,
  4;32,33,119,120;,
  4;26,27,61,62;,
  4;124,125,41,30;,
  4;43,111,112,37;,
  4;44,45,22,21;,
  4;45,87,88,22;,
  4;74,75,47,24;,
  4;47,48,25,24;,
  4;122,123,49,31;,
  4;50,51,27,26;,
  4;51,67,68,27;,
  4;82,83,53,29;,
  4;53,42,20,29;,
  4;49,91,92,31;,
  4;92,93,63,31;,
  4;94,95,33,32;,
  4;95,96,71,33;,
  4;98,99,35,79;,
  4;99,100,36,35;,
  4;101,102,37,57;,
  4;102,103,43,37;,
  4;39,38,104,105;,
  4;105,106,85,39;,
  4;41,77,108,109;,
  4;30,41,109,90;,
  4;38,43,103,104;,
  4;110,111,43,38;,
  4;15,45,44,6;,
  4;86,87,45,15;,
  4;16,47,75,76;,
  4;4,48,47,16;,
  4;30,49,123,124;,
  4;90,91,49,30;,
  4;19,51,50,2;,
  4;66,67,51,19;,
  4;12,53,83,84;,
  4;0,42,53,12;,
  4;55,89,78,14;,
  4;56,55,14,7;,
  4;36,57,113,114;,
  4;100,101,57,36;,
  4;59,58,1,13;,
  4;80,81,59,13;,
  4;61,69,70,18;,
  4;62,61,18,3;,
  4;32,63,93,94;,
  4;120,121,63,32;,
  4;65,64,5,17;,
  4;72,130,65,17;,
  4;8,52,67,66;,
  4;68,67,52,28;,
  4;69,68,28,60;,
  4;70,69,60,9;,
  4;96,97,34,71;,
  4;117,118,71,34;,
  4;54,73,72,10;,
  4;23,74,73,54;,
  4;46,75,74,23;,
  4;76,75,46,11;,
  4;126,127,40,77;,
  4;107,108,77,40;,
  4;34,79,116,117;,
  4;97,98,79,34;,
  4;60,81,80,9;,
  4;28,82,81,60;,
  4;52,83,82,28;,
  4;84,83,52,8;,
  4;40,85,106,107;,
  4;127,128,85,40;,
  4;11,46,87,86;,
  4;88,87,46,23;,
  4;89,88,23,54;,
  4;78,89,54,10;,
  4;2,50,91,90;,
  4;92,91,50,26;,
  4;62,93,92,26;,
  4;94,93,62,3;,
  4;18,95,94,3;,
  4;70,96,95,18;,
  4;9,97,96,70;,
  4;80,98,97,9;,
  4;13,99,98,80;,
  4;1,100,99,13;,
  4;58,101,100,1;,
  4;20,102,101,58;,
  4;42,103,102,20;,
  4;104,103,42,0;,
  4;105,104,0,12;,
  4;84,106,105,12;,
  4;107,106,84,8;,
  4;66,108,107,8;,
  4;109,108,66,19;,
  4;90,109,19,2;,
  4;6,44,111,110;,
  4;112,111,44,21;,
  4;56,113,112,21;,
  4;114,113,56,7;,
  4;115,114,7,14;,
  4;78,116,115,14;,
  4;117,116,78,10;,
  4;72,118,117,10;,
  4;119,118,72,17;,
  4;120,119,17,5;,
  4;64,121,120,5;,
  4;25,122,121,64;,
  4;48,123,122,25;,
  4;124,123,48,4;,
  4;16,125,124,4;,
  4;76,126,125,16;,
  4;11,127,126,76;,
  4;86,128,127,11;,
  4;15,129,128,86;,
  4;6,110,129,15;;
 }
 MeshTextureCoords {
  161;
  0.500047;0.168755;,
  0.500047;0.174124;,
  0.513641;0.174124;,
  0.513641;0.168755;,
  0.513641;0.120808;,
  0.500047;0.120808;,
  0.500047;0.132609;,
  0.513641;0.132609;,
  0.513641;0.092830;,
  0.500047;0.092830;,
  0.500047;0.098199;,
  0.513641;0.098199;,
  0.500047;0.055139;,
  0.513641;0.055139;,
  0.513641;0.043338;,
  0.500047;0.043338;,
  0.546371;0.168755;,
  0.546371;0.174124;,
  0.558172;0.174124;,
  0.558172;0.168755;,
  0.441828;0.168755;,
  0.441828;0.174124;,
  0.453629;0.174124;,
  0.453629;0.168755;,
  0.513641;0.187900;,
  0.500047;0.187900;,
  0.500047;0.193701;,
  0.513641;0.193701;,
  0.558172;0.193701;,
  0.558172;0.187900;,
  0.546371;0.187900;,
  0.546371;0.193701;,
  0.500047;0.073252;,
  0.500047;0.079054;,
  0.513641;0.079054;,
  0.513641;0.073252;,
  0.441828;0.187900;,
  0.441828;0.193701;,
  0.453629;0.193701;,
  0.453629;0.187900;,
  0.500047;0.201732;,
  0.513641;0.201732;,
  0.546371;0.201732;,
  0.558172;0.201732;,
  0.500047;0.065222;,
  0.513641;0.065222;,
  0.441828;0.201732;,
  0.453629;0.201732;,
  0.500047;0.110725;,
  0.513641;0.110725;,
  0.546371;0.156229;,
  0.558172;0.156229;,
  0.500047;0.156229;,
  0.513641;0.156229;,
  0.441828;0.156229;,
  0.453629;0.156229;,
  0.486461;0.043338;,
  0.486461;0.055139;,
  0.486461;0.065222;,
  0.486461;0.073252;,
  0.486461;0.079054;,
  0.486461;0.092830;,
  0.486461;0.098199;,
  0.486461;0.110725;,
  0.486461;0.120808;,
  0.486461;0.132609;,
  0.486461;0.156229;,
  0.486461;0.168755;,
  0.486461;0.174124;,
  0.486461;0.187900;,
  0.486461;0.193701;,
  0.486461;0.201732;,
  0.486461;0.143193;,
  0.500047;0.143193;,
  0.513641;0.143193;,
  0.535788;0.156229;,
  0.535788;0.168755;,
  0.535788;0.174124;,
  0.535788;0.187900;,
  0.535788;0.193701;,
  0.535788;0.201732;,
  0.513641;0.032755;,
  0.500047;0.032755;,
  0.486461;0.032755;,
  0.464212;0.201732;,
  0.464212;0.193701;,
  0.464212;0.187900;,
  0.464212;0.174124;,
  0.464212;0.168755;,
  0.464212;0.156229;,
  0.477248;0.043338;,
  0.477248;0.032755;,
  0.477248;0.055139;,
  0.477248;0.073252;,
  0.477248;0.065222;,
  0.477248;0.079054;,
  0.477248;0.098199;,
  0.477248;0.092830;,
  0.477248;0.110725;,
  0.477248;0.132609;,
  0.477248;0.120808;,
  0.477248;0.143193;,
  0.477248;0.168755;,
  0.477248;0.156229;,
  0.477248;0.174124;,
  0.477248;0.193701;,
  0.477248;0.187900;,
  0.477248;0.201732;,
  0.522752;0.079054;,
  0.522752;0.073252;,
  0.522752;0.065222;,
  0.522752;0.043338;,
  0.522752;0.055139;,
  0.522752;0.032755;,
  0.522752;0.201732;,
  0.522752;0.193701;,
  0.522752;0.187900;,
  0.522752;0.174124;,
  0.522752;0.168755;,
  0.522752;0.156229;,
  0.522752;0.132609;,
  0.522752;0.143193;,
  0.522752;0.120808;,
  0.522752;0.110725;,
  0.522752;0.098199;,
  0.522752;0.092830;,
  0.477248;0.179875;,
  0.486461;0.179875;,
  0.500047;0.179875;,
  0.513641;0.179875;,
  0.522752;0.179875;,
  0.535788;0.179875;,
  0.546371;0.179875;,
  0.558172;0.179875;,
  0.513641;0.087079;,
  0.522752;0.087079;,
  0.500047;0.087079;,
  0.486461;0.087079;,
  0.477248;0.087079;,
  0.441828;0.179875;,
  0.453629;0.179875;,
  0.464212;0.179875;,
  0.513641;0.019719;,
  0.522752;0.019719;,
  0.500047;0.019719;,
  0.486461;0.019719;,
  0.477248;0.019719;,
  0.568255;0.201732;,
  0.568255;0.193701;,
  0.568255;0.187900;,
  0.568255;0.179875;,
  0.568255;0.174124;,
  0.568255;0.168755;,
  0.568255;0.156229;,
  0.431745;0.168755;,
  0.431745;0.156229;,
  0.431745;0.174124;,
  0.431745;0.179875;,
  0.431745;0.187900;,
  0.431745;0.193701;,
  0.431745;0.201732;;
 }
}
