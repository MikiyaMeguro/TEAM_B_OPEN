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
 7.54450;1.29727;0.20499;,
 6.18612;1.53173;0.18099;,
 6.16732;1.50556;0.97383;,
 7.52925;1.27606;0.84751;,
 8.18584;-0.17189;0.60027;,
 8.19708;-0.23805;0.16910;,
 8.19114;0.20379;0.18353;,
 8.17902;0.18700;0.69234;,
 6.20299;-1.14895;0.88706;,
 6.22183;-1.12277;0.09423;,
 7.57344;-0.85398;0.13466;,
 7.55817;-0.87521;0.77717;,
 0.09061;-0.73168;-0.03819;,
 0.18558;-0.71994;0.85715;,
 0.05766;0.04597;0.91915;,
 0.07975;0.07669;-0.01177;,
 7.53401;0.14520;1.24164;,
 6.17321;0.11015;1.46018;,
 6.18248;-0.57830;1.43767;,
 7.54153;-0.41275;1.22342;,
 7.59257;-0.34174;-0.92742;,
 6.24550;-0.49070;-1.21628;,
 6.23622;0.19776;-1.19379;,
 7.58505;0.21620;-0.90918;,
 3.05286;1.86013;1.15287;,
 3.07734;1.89423;0.12002;,
 2.09042;1.88175;0.09618;,
 2.06594;1.84766;1.12906;,
 2.08567;-0.86706;1.73331;,
 3.07259;-0.85456;1.75714;,
 3.06054;0.04232;1.78647;,
 2.07364;0.02984;1.76264;,
 2.13693;-1.57636;-0.01685;,
 3.12382;-1.56388;0.00698;,
 3.09934;-1.59798;1.03984;,
 2.11241;-1.61046;1.01601;,
 3.15467;-0.74044;-1.70026;,
 2.16773;-0.75294;-1.72410;,
 2.15566;0.14396;-1.69479;,
 3.14257;0.15643;-1.67095;,
 0.45566;1.54979;0.04580;,
 0.63483;1.45956;0.82833;,
 0.44186;0.03122;1.41226;,
 0.62962;-0.63966;1.33418;,
 0.49375;-1.28583;-0.04691;,
 0.67115;-1.24211;0.74000;,
 0.69403;-0.55006;-1.38028;,
 0.50913;0.12481;-1.42279;,
 7.91422;-0.54892;0.15217;,
 7.90463;-0.42431;0.48412;,
 7.88585;0.17095;0.94971;,
 7.89249;-0.10501;0.81860;,
 7.89335;1.00094;0.20283;,
 7.88742;0.85472;0.52591;,
 7.92350;-0.06192;-0.48703;,
 7.92263;0.22209;-0.59985;,
 0.10181;0.10740;-0.94220;,
 0.22734;-0.66130;-0.92502;,
 0.70722;-1.19095;-0.81982;,
 2.16141;-1.54229;-1.04913;,
 3.14834;-1.52982;-1.02530;,
 6.24061;-1.09662;-0.69815;,
 7.58869;-0.83278;-0.50753;,
 7.92014;-0.40330;-0.17131;,
 8.20617;-0.14399;-0.25696;,
 8.20319;0.22057;-0.32501;,
 7.90295;0.87698;-0.12945;,
 7.55975;1.31845;-0.43720;,
 6.20494;1.55788;-0.61140;,
 3.10184;1.92831;-0.91227;,
 2.11495;1.91582;-0.93607;,
 0.67092;1.51134;-0.73149;,
 8.19718;0.54824;-0.24786;,
 8.18584;0.60001;0.19649;,
 8.17621;0.51872;0.63643;,
 7.88478;0.43341;0.85684;,
 7.52731;0.64553;1.25801;,
 6.16492;0.72753;1.48035;,
 3.04972;0.84660;1.81276;,
 2.06283;0.83411;1.78893;,
 0.58214;0.64414;1.38561;,
 0.14607;0.74020;0.91114;,
 0.07000;0.80158;0.01191;,
 0.18821;0.79961;-0.88442;,
 0.64702;0.73439;-1.34920;,
 2.14487;0.94825;-1.66847;,
 3.13178;0.96072;-1.64466;,
 6.22790;0.81513;-1.17359;,
 7.57837;0.71653;-0.89281;,
 7.91670;0.47788;-0.49004;,
 0.50913;0.12481;-1.42279;,
 0.64702;0.73439;-1.34920;,
 0.69403;-0.55006;-1.38028;,
 2.52614;-1.25124;-1.44668;,
 1.11139;-1.03418;-1.22813;,
 3.35387;-1.24076;-1.42669;,
 7.61347;-0.65558;-0.75850;,
 6.02407;-0.88021;-1.01465;,
 7.92421;-0.30457;-0.39067;,
 7.92263;0.22209;-0.59985;,
 7.92350;-0.06192;-0.48703;,
 7.91670;0.47788;-0.49004;,
 7.55449;1.14827;-0.70038;,
 7.90944;0.79292;-0.35479;,
 6.11729;1.44810;-1.03290;,
 2.48715;1.64910;-1.35186;,
 3.31488;1.65960;-1.33189;,
 1.07897;1.37865;-1.14927;,
 3.28506;-1.33648;1.47307;,
 2.23813;-1.50168;1.59011;,
 1.05414;-1.11381;1.18422;,
 0.44186;0.03122;1.41226;,
 0.62962;-0.63966;1.33418;,
 0.58214;0.64414;1.38561;,
 1.02170;1.29903;1.26309;,
 2.41833;1.55339;1.54790;,
 3.24607;1.56386;1.56788;,
 5.94133;1.27269;1.28402;,
 7.01946;0.99974;1.00227;,
 7.88343;0.75671;0.74249;,
 7.88585;0.17095;0.94971;,
 7.88478;0.43341;0.85684;,
 7.89249;-0.10501;0.81860;,
 7.89821;-0.34079;0.70660;,
 7.50444;-0.70810;0.80327;,
 5.97125;-0.95367;1.21124;,
 4.71716;1.63905;-1.26219;,
 4.72412;1.90361;-0.84814;,
 4.70026;1.87042;0.15766;,
 4.67637;1.83719;1.16402;,
 4.65010;1.54580;1.56320;,
 4.67332;0.84965;1.80697;,
 4.68385;0.06599;1.78136;,
 4.69561;-0.80787;1.75280;,
 4.72165;-1.53221;1.05387;,
 4.68809;-1.28016;1.47082;,
 4.74554;-1.49901;0.04753;,
 4.76940;-1.46580;-0.95830;,
 4.75514;-1.18690;-1.35457;,
 4.77555;-0.69669;-1.61595;,
 4.77860;0.17822;-1.43159;,
 4.75325;0.96083;-1.56176;,
 0.63483;1.45956;0.82833;,
 1.02170;1.29903;1.26309;,
 0.45566;1.54979;0.04580;,
 0.67092;1.51134;-0.73149;,
 1.07897;1.37865;-1.14927;,
 1.05414;-1.11381;1.18422;,
 2.23813;-1.50168;1.59011;,
 3.28506;-1.33648;1.47307;,
 4.68809;-1.28016;1.47082;,
 5.97125;-0.95367;1.21124;,
 7.50444;-0.70810;0.80327;,
 7.89821;-0.34079;0.70660;,
 7.61347;-0.65558;-0.75850;,
 7.92421;-0.30457;-0.39067;,
 6.02407;-0.88021;-1.01465;,
 4.75514;-1.18690;-1.35457;,
 3.35387;-1.24076;-1.42669;,
 2.52614;-1.25124;-1.44668;,
 1.11139;-1.03418;-1.22813;;
 
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
  -0.353013;0.596347;-0.720939;,
  -0.389639;0.544478;0.742782;,
  0.776161;0.447183;-0.444523;,
  0.636446;0.460276;0.618936;,
  0.781969;-0.428745;-0.452441;,
  0.690988;-0.463620;0.554610;,
  -0.321548;-0.626337;-0.710148;,
  -0.415809;-0.656292;0.629590;,
  0.147836;0.655457;-0.740622;,
  0.137364;0.583973;0.800067;,
  0.157183;-0.691594;0.704976;,
  0.190890;-0.648876;-0.736560;,
  -0.124202;0.640160;-0.758135;,
  -0.161132;0.585235;0.794693;,
  -0.144619;-0.709694;0.689507;,
  -0.110638;-0.657115;-0.745627;,
  0.588099;-0.541788;-0.600504;,
  0.513206;-0.515563;0.686159;,
  0.453819;0.492590;0.742565;,
  0.588378;0.552933;-0.589980;,
  -0.587416;0.809179;0.013061;,
  -0.512963;-0.857470;-0.040184;,
  -0.097356;-0.994632;-0.035065;,
  0.144994;-0.989002;-0.029201;,
  0.487320;-0.873056;-0.017079;,
  0.713304;-0.700831;-0.005764;,
  0.744360;0.666576;0.040063;,
  0.463700;0.885071;0.040393;,
  0.118356;0.992334;0.035564;,
  -0.124052;0.991826;0.029870;,
  0.696240;0.023647;-0.717420;,
  0.999629;0.012642;0.024139;,
  0.658992;-0.024939;0.751737;,
  0.448561;-0.026684;0.893354;,
  0.108174;-0.031025;0.993648;,
  -0.131027;-0.035545;0.990741;,
  -0.516401;-0.040023;0.855411;,
  -0.999589;-0.015534;-0.024101;,
  -0.477943;0.017152;-0.878223;,
  -0.083881;0.030041;-0.996023;,
  0.148452;0.028922;-0.988497;,
  0.490426;0.031561;-0.870911;,
  -0.511557;0.758240;-0.404204;,
  -0.913207;-0.004196;-0.407475;,
  -0.447785;-0.781273;-0.434857;,
  -0.108895;-0.928478;-0.355063;,
  0.174151;-0.928683;-0.327444;,
  0.543561;-0.792836;-0.275595;,
  0.727932;-0.615422;-0.302277;,
  0.917797;0.018966;-0.396598;,
  0.752807;0.605490;-0.258192;,
  0.524447;0.827422;-0.200820;,
  0.131500;0.964548;-0.228810;,
  -0.134316;0.943242;-0.303734;,
  0.160002;-0.949253;0.270775;,
  -0.113572;-0.977225;0.179257;,
  -0.481595;-0.821534;0.305202;,
  -0.930298;-0.029695;0.365602;,
  -0.532385;0.730959;0.426926;,
  -0.149921;0.922565;0.355524;,
  0.134908;0.930116;0.341589;,
  0.505799;0.695736;0.510018;,
  0.711200;0.549065;0.439002;,
  0.896556;-0.008821;0.442842;,
  0.693751;-0.602133;0.395153;,
  0.535300;-0.707991;0.460654;,
  0.255399;0.650595;-0.715191;,
  0.221634;0.955410;-0.195117;,
  0.195506;0.980005;0.036983;,
  0.248174;0.867745;0.430615;,
  0.253924;0.543057;0.800382;,
  0.185455;-0.029609;0.982207;,
  0.256078;-0.631280;0.732059;,
  0.254438;-0.950080;0.180582;,
  0.221786;-0.974724;-0.026912;,
  0.257236;-0.907577;-0.331865;,
  0.270603;-0.635721;-0.722933;,
  0.202475;0.032079;-0.978762;,
  0.060532;-0.707549;0.704067;,
  -0.010046;-0.032808;0.999411;,
  -0.009524;0.596534;0.802531;,
  -0.003659;0.946086;0.323894;,
  0.000235;0.999455;0.032998;,
  0.010260;0.964742;-0.262999;,
  0.027371;0.651939;-0.757778;,
  0.060542;0.030701;-0.997693;,
  0.043937;-0.661854;-0.748344;,
  0.035698;-0.948130;-0.315872;,
  0.027094;-0.999110;-0.032334;,
  0.048052;-0.978991;0.198163;,
  0.715871;0.313366;-0.623964;,
  0.840712;0.394506;-0.370902;,
  0.939538;0.340774;0.033783;,
  0.819852;0.368835;0.437955;,
  0.646869;0.358333;0.673170;,
  0.462211;0.337634;0.819978;,
  0.224796;0.233137;0.946104;,
  0.119712;0.162669;0.979392;,
  -0.010669;0.150173;0.988602;,
  -0.142520;0.182759;0.972773;,
  -0.480017;0.277157;0.832327;,
  -0.853051;0.322497;0.410243;,
  -0.955588;0.294434;-0.012696;,
  -0.833406;0.351223;-0.426704;,
  -0.441234;0.337434;-0.831535;,
  -0.097168;0.254366;-0.962214;,
  0.048231;0.199027;-0.978806;,
  0.150038;0.156862;-0.976157;,
  0.224662;0.162035;-0.960870;,
  0.523597;0.214666;-0.824478;,
  -0.425759;-0.356672;-0.831573;,
  -0.795440;-0.402588;-0.452988;,
  -0.924556;-0.379510;-0.034183;,
  -0.815318;-0.429072;0.388785;,
  -0.480221;-0.357734;0.800884;,
  -0.138472;-0.227591;0.963861;,
  0.018953;-0.233359;0.972206;,
  0.132496;-0.291715;0.947284;,
  0.235628;-0.352416;0.905695;,
  0.514448;-0.374602;0.771373;,
  0.672058;-0.375100;0.638465;,
  0.789383;-0.433564;0.434624;,
  0.923879;-0.382563;0.009589;,
  0.811590;-0.404226;-0.421810;,
  0.716697;-0.280269;-0.638588;,
  0.542367;-0.215160;-0.812123;,
  0.245392;-0.224026;-0.943183;,
  0.175690;-0.195888;-0.964759;,
  0.054037;-0.204614;-0.977350;,
  -0.098843;-0.265220;-0.959108;,
  0.208043;-0.448991;0.868980;;
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
