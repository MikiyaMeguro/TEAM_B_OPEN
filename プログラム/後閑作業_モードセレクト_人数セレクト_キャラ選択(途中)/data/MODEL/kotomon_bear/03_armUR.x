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
 -6.90378;2.72916;0.03945;,
 -5.70247;2.73085;0.00498;,
 -5.60086;2.48815;-1.14296;,
 -6.67031;2.48665;-1.11227;,
 -9.07100;0.08113;-1.00565;,
 -8.96942;-0.74422;-0.95738;,
 -9.04215;-0.86283;-0.04604;,
 -9.04242;0.04251;-0.01090;,
 -6.66900;-2.16642;-1.29292;,
 -5.59953;-2.16491;-1.32360;,
 -5.70097;-2.49595;-0.19793;,
 -6.90228;-2.49764;-0.16347;,
 -0.16954;-0.83162;-1.32176;,
 -0.17380;0.08846;-1.42567;,
 -0.14051;0.04352;-0.26737;,
 -0.14020;-1.01065;-0.30831;,
 -6.97797;0.11733;-2.67278;,
 -5.77662;0.11900;-2.70725;,
 -5.68467;-0.97049;-2.54117;,
 -6.78918;-0.97205;-2.50947;,
 -6.65108;-1.15849;2.29415;,
 -5.54657;-1.15695;2.26247;,
 -5.62644;-0.08378;2.51743;,
 -6.82777;-0.08546;2.55189;,
 -1.68496;2.49364;-1.25533;,
 -3.10098;2.49165;-1.21469;,
 -3.06211;2.73455;-0.07077;,
 -1.64748;2.73654;-0.11137;,
 -1.59417;-0.96478;-2.65854;,
 -3.08026;-0.96686;-2.61590;,
 -3.07878;0.12278;-2.78465;,
 -1.60386;0.12484;-2.82697;,
 -1.58509;-2.49020;-0.31604;,
 -3.03090;-2.49222;-0.27455;,
 -3.08611;-2.16140;-1.39573;,
 -1.65590;-2.15941;-1.43676;,
 -2.95594;-1.15331;2.18813;,
 -1.48428;-1.15127;2.14590;,
 -1.51170;-0.07803;2.39936;,
 -2.95693;-0.08005;2.44082;,
 -0.52095;2.07477;-0.16806;,
 -0.54422;1.85806;-0.98896;,
 -0.57630;0.12580;-2.19192;,
 -0.56937;-0.61315;-1.98608;,
 -0.51984;-1.82547;-0.31947;,
 -0.54324;-1.54577;-1.12111;,
 -0.47076;-0.74629;1.44422;,
 -0.46421;-0.02552;1.70671;,
 -8.66154;-1.56155;-0.07460;,
 -8.50737;-1.38390;-0.83597;,
 -8.71003;0.11422;-1.68270;,
 -8.53960;-0.57944;-1.57470;,
 -8.66249;1.78804;0.05543;,
 -8.50825;1.67002;-0.71740;,
 -8.45136;-0.69858;1.49456;,
 -8.61377;-0.01574;1.66553;,
 -0.10079;-0.01010;1.11399;,
 -0.10531;-0.89219;0.91389;,
 -0.49210;-1.56829;0.66071;,
 -1.59162;-2.20206;1.05105;,
 -3.01890;-2.20405;1.09199;,
 -5.50294;-2.20753;1.16327;,
 -6.54767;-2.20899;1.19325;,
 -8.42629;-1.42099;0.83573;,
 -8.89336;-0.80621;1.04213;,
 -9.00830;-0.00354;1.17545;,
 -8.42713;1.57746;0.95213;,
 -6.54898;2.33643;1.36971;,
 -5.50424;2.33789;1.33973;,
 -3.03069;2.34135;1.26875;,
 -1.61442;2.34334;1.22812;,
 -0.49303;1.74240;0.78923;,
 -8.88413;0.95381;1.10179;,
 -9.04272;1.10258;0.03027;,
 -8.96130;1.04769;-0.88099;,
 -8.52559;0.92676;-1.50479;,
 -6.77383;1.39312;-2.40019;,
 -5.67755;1.39463;-2.43164;,
 -3.08109;1.39829;-2.50615;,
 -1.59404;1.40037;-2.54881;,
 -0.56927;0.99071;-1.90391;,
 -0.16977;1.16558;-1.23238;,
 -0.14085;1.27783;-0.21946;,
 -0.10628;1.05146;0.97528;,
 -0.47180;0.85911;1.48664;,
 -1.48267;1.21527;2.21978;,
 -2.95654;1.21321;2.26207;,
 -5.54048;1.20960;2.33621;,
 -6.63678;1.20806;2.36768;,
 -8.43802;0.80854;1.54080;,
 -4.48518;0.12082;-2.74431;,
 -4.49727;-0.96884;-2.57524;,
 -4.49900;1.39631;-2.46545;,
 -4.41101;2.73269;-0.03208;,
 -4.45116;2.48977;-1.17595;,
 -4.38114;2.33946;1.30751;,
 -4.33497;-0.08198;2.48037;,
 -4.36192;1.21123;2.30240;,
 -4.35918;-1.15529;2.22840;,
 -4.37983;-2.20596;1.13105;,
 -4.40951;-2.49414;-0.23498;,
 -4.44984;-2.16332;-1.35660;,
 -6.13658;1.97738;-1.80093;,
 -8.37927;1.57134;-1.36367;,
 -5.31320;1.97852;-1.82457;,
 -4.42809;1.97978;-1.84997;,
 -3.26815;1.98138;-1.88325;,
 -2.05167;1.98308;-1.91815;,
 -0.56367;1.67684;-1.67544;,
 -0.52095;2.07477;-0.16806;,
 -0.54422;1.85806;-0.98896;,
 -0.49303;1.74240;0.78923;,
 -0.47779;1.56088;1.31204;,
 -1.94873;1.84412;1.66270;,
 -3.16519;1.84239;1.69761;,
 -4.32515;1.84079;1.73088;,
 -5.21027;1.83954;1.75629;,
 -6.03365;1.83840;1.77992;,
 -8.29859;1.46243;1.44187;,
 -0.56281;-1.31188;-1.79146;,
 -2.05066;-1.59924;-2.05723;,
 -3.26712;-1.60095;-2.02233;,
 -4.42707;-1.60257;-1.98903;,
 -5.46381;-1.80954;-2.18149;,
 -6.38546;-1.81082;-2.15506;,
 -8.37844;-1.23534;-1.47263;,
 -6.03262;-1.74395;1.64084;,
 -8.29780;-1.34423;1.33291;,
 -5.20924;-1.74280;1.61721;,
 -4.32413;-1.74155;1.59182;,
 -3.16418;-1.73993;1.55854;,
 -1.94770;-1.73823;1.52362;,
 -0.47693;-1.42783;1.19601;,
 -0.47180;0.85911;1.48664;,
 -0.47779;1.56088;1.31204;,
 -0.46421;-0.02552;1.70671;,
 -0.47076;-0.74629;1.44422;,
 -0.47693;-1.42783;1.19601;,
 -1.94770;-1.73823;1.52362;,
 -3.16418;-1.73993;1.55854;,
 -4.32413;-1.74155;1.59182;,
 -5.20924;-1.74280;1.61721;,
 -6.03262;-1.74395;1.64084;,
 -8.29780;-1.34423;1.33291;,
 -8.45136;-0.69858;1.49456;,
 -8.61377;-0.01574;1.66553;,
 -8.43802;0.80854;1.54080;,
 -3.26712;-1.60095;-2.02233;,
 -4.42707;-1.60257;-1.98903;,
 -2.05066;-1.59924;-2.05723;,
 -0.56281;-1.31188;-1.79146;,
 -0.56937;-0.61315;-1.98608;,
 -0.57630;0.12580;-2.19192;,
 -0.56927;0.99071;-1.90391;,
 -0.56367;1.67684;-1.67544;,
 -8.52559;0.92676;-1.50479;,
 -8.71003;0.11422;-1.68270;,
 -8.53960;-0.57944;-1.57470;,
 -8.37844;-1.23534;-1.47263;,
 -6.38546;-1.81082;-2.15506;,
 -5.46381;-1.80954;-2.18149;;
 
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
    "data\\TEXTURE\\kuma_uv.jpg";
   }
  }
 }
 MeshNormals {
  130;
  0.609897;0.534705;0.584906;,
  0.598231;0.594983;-0.536764;,
  -0.475108;0.576087;0.665128;,
  -0.528123;0.640837;-0.557148;,
  -0.472621;-0.635078;0.610987;,
  -0.575597;-0.584497;-0.571885;,
  0.609117;-0.582897;0.537781;,
  0.598469;-0.555288;-0.577485;,
  0.020626;0.659976;0.751003;,
  -0.019611;0.763016;-0.646082;,
  0.053891;-0.712053;-0.700054;,
  0.020905;-0.720318;0.693329;,
  0.247342;0.648337;0.720057;,
  0.208105;0.742100;-0.637165;,
  0.209556;-0.694022;-0.688781;,
  0.248182;-0.705727;0.663592;,
  -0.163632;-0.714418;0.680317;,
  -0.247603;-0.694043;-0.676015;,
  -0.203174;0.745628;-0.634634;,
  -0.163696;0.653546;0.738973;,
  0.731517;0.681803;0.005352;,
  0.740008;-0.670926;-0.047397;,
  0.280503;-0.958765;-0.045696;,
  0.000266;-0.999223;-0.039407;,
  -0.235256;-0.971417;-0.031679;,
  -0.670789;-0.741579;-0.010134;,
  -0.670213;0.740656;0.047362;,
  -0.235812;0.970815;0.043720;,
  -0.000304;0.999271;0.038178;,
  0.271229;0.962074;0.029143;,
  -0.601684;-0.042037;0.797627;,
  -0.999587;-0.004043;0.028470;,
  -0.694401;0.017062;-0.719386;,
  -0.272273;0.027183;-0.961836;,
  -0.028710;0.030639;-0.999118;,
  0.274568;0.028537;-0.961144;,
  0.730964;0.019694;-0.682132;,
  0.999588;0.001398;-0.028681;,
  0.719720;-0.035402;0.693361;,
  0.323279;-0.046384;0.945166;,
  0.028718;-0.046894;0.998487;,
  -0.216593;-0.047992;0.975082;,
  -0.019059;-0.714792;-0.699078;,
  -0.028709;0.030639;-0.999118;,
  -0.019602;0.763017;-0.646081;,
  -0.000302;0.999271;0.038179;,
  0.020623;0.659976;0.751004;,
  0.028717;-0.046896;0.998487;,
  0.020903;-0.720318;0.693329;,
  0.000267;-0.999223;-0.039406;,
  0.020630;0.659976;0.751004;,
  -0.000311;0.999271;0.038176;,
  -0.019612;0.763015;-0.646084;,
  -0.028712;0.030638;-0.999118;,
  0.056599;-0.711010;-0.700901;,
  0.000268;-0.999223;-0.039409;,
  0.020904;-0.720318;0.693329;,
  0.028712;-0.046895;0.998487;,
  -0.569138;0.354799;0.741755;,
  -0.948835;0.313335;0.039147;,
  -0.646036;0.404890;-0.647072;,
  -0.244718;0.474131;-0.845762;,
  -0.025662;0.491861;-0.870296;,
  -0.025664;0.491862;-0.870295;,
  -0.025656;0.491864;-0.870294;,
  0.251179;0.460003;-0.851649;,
  0.712216;0.327580;-0.620837;,
  0.970583;0.240050;-0.018585;,
  0.708755;0.287822;0.644069;,
  0.298252;0.390073;0.871142;,
  0.025399;0.422922;0.905810;,
  0.025400;0.422924;0.905809;,
  0.025401;0.422921;0.905810;,
  -0.194749;0.406654;0.892584;,
  0.704531;-0.350804;0.616905;,
  0.971321;-0.234871;-0.037025;,
  0.712030;-0.290181;-0.639381;,
  0.252015;-0.407076;-0.877939;,
  -0.025209;-0.435622;-0.899777;,
  0.011518;-0.393331;-0.919325;,
  0.009867;-0.314734;-0.949129;,
  -0.258815;-0.302780;-0.917245;,
  -0.656446;-0.328985;-0.678858;,
  -0.948118;-0.317580;0.014666;,
  -0.567548;-0.429093;0.702687;,
  -0.196225;-0.490555;0.849030;,
  0.025473;-0.504054;0.863296;,
  0.025480;-0.504056;0.863295;,
  0.025477;-0.504056;0.863295;,
  0.294422;-0.470677;0.831732;,
  0.707269;0.615819;0.347184;,
  0.931705;0.242889;0.270056;,
  0.960523;-0.013958;0.277849;,
  0.931194;-0.267201;0.247957;,
  0.711384;-0.636542;0.297903;,
  0.265604;-0.862484;0.430786;,
  0.014925;-0.878629;0.477271;,
  0.014926;-0.878630;0.477269;,
  0.014926;-0.878632;0.477267;,
  -0.192538;-0.867766;0.458160;,
  -0.591705;-0.696928;0.405187;,
  -0.846830;-0.368508;0.383511;,
  -0.915892;-0.022635;0.400787;,
  -0.848771;0.326606;0.415833;,
  -0.593276;0.659721;0.461294;,
  -0.193023;0.829527;0.524048;,
  0.014433;0.839001;0.543939;,
  0.014434;0.838997;0.543944;,
  0.014432;0.838998;0.543943;,
  0.259579;0.829803;0.494010;,
  0.024958;-0.894651;-0.446067;,
  -0.012688;-0.874516;-0.484831;,
  0.234902;-0.854914;-0.462541;,
  0.703580;-0.616089;-0.354133;,
  0.935393;-0.225302;-0.272541;,
  0.962704;0.008252;-0.270430;,
  0.935337;0.243431;-0.256685;,
  0.698900;0.646764;-0.305344;,
  0.228959;0.891049;-0.391931;,
  -0.013194;0.909467;-0.415568;,
  -0.013199;0.909467;-0.415566;,
  -0.013206;0.909468;-0.415565;,
  -0.216865;0.891449;-0.397855;,
  -0.627949;0.697432;-0.345352;,
  -0.892440;0.338172;-0.298646;,
  -0.957333;0.004922;-0.288944;,
  -0.890802;-0.323722;-0.318867;,
  -0.637526;-0.685876;-0.350907;,
  -0.225504;-0.910363;-0.346968;,
  0.026755;-0.928474;-0.370432;;
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
  4;74,93,92,38;,
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
  0.500056;0.715386;,
  0.500056;0.721753;,
  0.514746;0.721753;,
  0.514746;0.715386;,
  0.514746;0.672445;,
  0.514746;0.659081;,
  0.500056;0.659081;,
  0.500056;0.672445;,
  0.514746;0.631564;,
  0.514746;0.625197;,
  0.500056;0.625197;,
  0.500056;0.631564;,
  0.514746;0.579750;,
  0.514746;0.566387;,
  0.500056;0.566387;,
  0.500056;0.579750;,
  0.555090;0.715386;,
  0.555090;0.721753;,
  0.568454;0.721753;,
  0.568454;0.715386;,
  0.431546;0.715386;,
  0.431546;0.721753;,
  0.444910;0.721754;,
  0.444910;0.715386;,
  0.514746;0.745024;,
  0.514746;0.736616;,
  0.500056;0.736616;,
  0.500056;0.745024;,
  0.568454;0.745024;,
  0.568454;0.736616;,
  0.555090;0.736616;,
  0.555090;0.745024;,
  0.500056;0.601926;,
  0.500056;0.610335;,
  0.514746;0.610335;,
  0.514746;0.601926;,
  0.431546;0.736616;,
  0.431546;0.745024;,
  0.444910;0.745024;,
  0.444910;0.736616;,
  0.500056;0.754565;,
  0.514746;0.754565;,
  0.555090;0.754565;,
  0.568454;0.754565;,
  0.500056;0.592386;,
  0.514746;0.592386;,
  0.431546;0.754565;,
  0.444910;0.754565;,
  0.500056;0.646446;,
  0.514746;0.646446;,
  0.555090;0.700505;,
  0.568454;0.700505;,
  0.500056;0.700505;,
  0.514746;0.700505;,
  0.431546;0.700505;,
  0.444910;0.700505;,
  0.482538;0.566387;,
  0.482538;0.579750;,
  0.482538;0.592386;,
  0.482538;0.601926;,
  0.482538;0.610335;,
  0.482538;0.625197;,
  0.482538;0.631564;,
  0.482538;0.646446;,
  0.482538;0.659081;,
  0.482538;0.672445;,
  0.482538;0.700505;,
  0.482538;0.715386;,
  0.482538;0.721754;,
  0.482538;0.736616;,
  0.482538;0.745024;,
  0.482538;0.754565;,
  0.482538;0.688092;,
  0.500056;0.688092;,
  0.514746;0.688092;,
  0.539443;0.700505;,
  0.539443;0.715386;,
  0.539443;0.721754;,
  0.539443;0.736616;,
  0.539443;0.745024;,
  0.539443;0.754565;,
  0.514746;0.550739;,
  0.500056;0.550739;,
  0.482538;0.550739;,
  0.460557;0.754565;,
  0.460557;0.745024;,
  0.460557;0.736616;,
  0.460557;0.721754;,
  0.460557;0.715386;,
  0.460557;0.700505;,
  0.555090;0.728598;,
  0.568454;0.728598;,
  0.539443;0.728598;,
  0.500056;0.728598;,
  0.514746;0.728598;,
  0.482538;0.728598;,
  0.444910;0.728598;,
  0.460557;0.728598;,
  0.431546;0.728598;,
  0.482538;0.618352;,
  0.500056;0.618352;,
  0.514746;0.618352;,
  0.527030;0.715386;,
  0.527030;0.700505;,
  0.527030;0.721754;,
  0.527030;0.728598;,
  0.527030;0.736616;,
  0.527030;0.745024;,
  0.527030;0.754565;,
  0.500056;0.538326;,
  0.514746;0.538326;,
  0.482538;0.538326;,
  0.472970;0.754565;,
  0.472970;0.745024;,
  0.472970;0.736616;,
  0.472970;0.728598;,
  0.472970;0.721754;,
  0.472970;0.715386;,
  0.472970;0.700505;,
  0.581089;0.754565;,
  0.581089;0.745024;,
  0.581089;0.736616;,
  0.581089;0.728598;,
  0.581089;0.721753;,
  0.581089;0.715386;,
  0.581089;0.700505;,
  0.418911;0.715386;,
  0.418911;0.700505;,
  0.418911;0.721753;,
  0.418911;0.728598;,
  0.418911;0.736616;,
  0.418911;0.745024;,
  0.418911;0.754565;,
  0.472970;0.550739;,
  0.472970;0.538326;,
  0.472970;0.566387;,
  0.472970;0.579750;,
  0.472970;0.592386;,
  0.472970;0.601926;,
  0.472970;0.610335;,
  0.472970;0.618352;,
  0.472970;0.625197;,
  0.472970;0.631564;,
  0.472970;0.646446;,
  0.472970;0.659081;,
  0.472970;0.672445;,
  0.472970;0.688092;,
  0.527030;0.610335;,
  0.527030;0.618352;,
  0.527030;0.601926;,
  0.527030;0.592386;,
  0.527030;0.579750;,
  0.527030;0.566387;,
  0.527030;0.550739;,
  0.527030;0.538326;,
  0.527030;0.688092;,
  0.527030;0.672445;,
  0.527030;0.659081;,
  0.527030;0.646446;,
  0.527030;0.631564;,
  0.527030;0.625197;;
 }
}
