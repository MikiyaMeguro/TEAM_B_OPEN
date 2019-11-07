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
 195;
 0.13415;-0.27195;2.87939;,
 1.33227;-0.28416;2.68568;,
 0.11690;-0.31539;2.11304;,
 1.05692;-0.30936;2.23636;,
 0.99021;-0.32467;1.96518;,
 2.78226;-0.31829;2.10979;,
 3.48213;-0.37760;1.07670;,
 2.32365;-0.38038;1.00668;,
 2.13375;-0.33740;1.76110;,
 2.42855;-0.50771;-1.23611;,
 2.38466;-0.45445;-0.29779;,
 3.24100;-0.46555;-0.47825;,
 2.90910;-0.52274;-1.49258;,
 0.94627;-0.51159;-1.33099;,
 2.57271;-0.55003;-1.97962;,
 0.03963;-0.55334;-2.08311;,
 0.05904;-0.50966;-1.31285;,
 -2.72601;-0.50952;-1.36026;,
 -3.47032;-0.36133;1.23924;,
 -2.58741;-0.36884;1.12263;,
 -2.48316;-0.49613;-1.11988;,
 -2.08780;-0.32752;1.85981;,
 -2.69589;-0.29566;2.41084;,
 -2.21499;-0.54664;-2.00554;,
 -1.52220;-0.50344;-1.23168;,
 -1.11991;-0.50344;-1.22431;,
 -1.00915;-0.54985;-2.04063;,
 -1.03117;-0.32099;1.99416;,
 -1.58660;-0.27178;2.85170;,
 0.11864;-0.94828;2.92509;,
 -1.58660;-0.27178;2.85170;,
 -1.75757;-1.72457;3.01580;,
 0.11317;-1.72833;2.97864;,
 1.45353;-1.73118;2.95225;,
 1.42577;-0.95452;2.84291;,
 2.89987;-1.94305;2.56316;,
 3.68020;-1.98365;1.03251;,
 3.66391;-1.05957;1.03088;,
 2.89880;-0.98032;2.41491;,
 2.88525;-1.61057;-1.79681;,
 3.40466;-1.35301;-0.69466;,
 3.41325;-2.31916;-0.81409;,
 3.05326;-2.53119;-2.00292;,
 0.02992;-1.43202;-2.15244;,
 2.42793;-1.62531;-2.06476;,
 2.46524;-2.46287;-2.12408;,
 0.36598;-2.29294;-2.14325;,
 0.03963;-0.55334;-2.08311;,
 0.02992;-1.43202;-2.15244;,
 -1.00915;-0.54985;-2.04063;,
 -2.19231;-1.43253;-2.20120;,
 -2.21499;-0.54664;-2.00554;,
 -2.22194;-1.04334;-2.24049;,
 -2.88624;-2.40071;-1.87156;,
 -3.75111;-1.82716;1.17145;,
 -3.70238;-1.04272;1.19169;,
 -2.86669;-1.40231;-1.67602;,
 -2.84999;-0.96732;2.54040;,
 -2.93848;-1.93090;2.80556;,
 0.99021;-0.32467;1.96518;,
 2.90910;-0.52274;-1.49258;,
 2.42855;-0.50771;-1.23611;,
 3.05326;-2.53119;-2.00292;,
 2.46524;-2.46287;-2.12408;,
 2.42793;-1.62531;-2.06476;,
 2.88525;-1.61057;-1.79681;,
 -2.22194;-1.04334;-2.24049;,
 -2.72601;-0.50952;-1.36026;,
 -2.19231;-1.43253;-2.20120;,
 -2.86669;-1.40231;-1.67602;,
 -2.48316;-0.49613;-1.11988;,
 -2.13489;-0.27603;2.76686;,
 -1.54768;-0.32418;1.92849;,
 -2.35814;-1.73225;2.86969;,
 -2.34017;-0.94728;2.90329;,
 -1.57092;-3.61277;3.19754;,
 -1.41179;-4.57155;3.21315;,
 -0.00644;-4.59486;3.26948;,
 0.04210;-3.63139;3.29355;,
 -2.12038;-4.53034;2.89183;,
 -2.44456;-3.66252;2.94725;,
 -3.22242;-3.81239;1.15333;,
 -2.64063;-4.50506;1.11897;,
 -2.13552;-4.72281;-1.36132;,
 -2.64063;-4.50506;1.11897;,
 -3.22242;-3.81239;1.15333;,
 -2.61968;-4.17906;-2.07046;,
 -2.61968;-4.17906;-2.07046;,
 -1.36386;-4.14124;-2.19029;,
 -1.39081;-4.78262;-1.50049;,
 -2.13552;-4.72281;-1.36132;,
 -1.10005;-4.78955;-1.52328;,
 0.99562;-4.17100;-2.23138;,
 0.85642;-4.84105;-1.55929;,
 -0.09066;-4.81540;-1.55931;,
 -0.04958;-4.14234;-2.23506;,
 2.01673;-4.82833;-1.45494;,
 2.50096;-4.15965;-2.05511;,
 2.50096;-4.15965;-2.05511;,
 2.80368;-4.06996;-0.84236;,
 2.17076;-4.74842;-0.41675;,
 2.01673;-4.82833;-1.45494;,
 1.94742;-4.63741;2.81699;,
 2.38493;-4.63735;1.02650;,
 3.03594;-3.77197;1.04176;,
 2.37012;-3.78381;2.93688;,
 2.37012;-3.78381;2.93688;,
 1.20278;-3.67915;3.20002;,
 1.02243;-4.62823;3.25099;,
 1.94742;-4.63741;2.81699;,
 -0.00644;-4.59486;3.26948;,
 0.04210;-3.63139;3.29355;,
 1.01533;-0.37706;1.04218;,
 -2.17936;-0.36659;1.16947;,
 -1.50659;-0.37013;1.11896;,
 0.99021;-0.32467;1.96518;,
 0.15148;-0.37522;1.05896;,
 0.97517;-0.45531;-0.33812;,
 2.38466;-0.45445;-0.29779;,
 0.20955;-0.47583;-0.71368;,
 -1.72179;-2.84090;3.15103;,
 -2.64261;-2.82903;3.04002;,
 0.05590;-2.88187;3.16813;,
 0.05590;-2.88187;3.16813;,
 1.33305;-2.91770;3.08814;,
 1.45353;-1.73118;2.95225;,
 0.11317;-1.72833;2.97864;,
 2.89987;-1.94305;2.56316;,
 2.79486;-2.96572;2.92802;,
 2.79486;-2.96572;2.92802;,
 3.38898;-3.11183;1.05212;,
 3.05326;-2.53119;-2.00292;,
 3.41325;-2.31916;-0.81409;,
 3.14468;-3.23705;-0.83614;,
 2.81585;-3.25543;-2.05210;,
 2.81585;-3.25543;-2.05210;,
 2.29026;-3.25480;-2.19186;,
 2.46524;-2.46287;-2.12408;,
 3.05326;-2.53119;-2.00292;,
 0.03122;-3.20643;-2.13286;,
 2.46524;-2.46287;-2.12408;,
 2.29026;-3.25480;-2.19186;,
 -0.01938;-3.82327;-2.18347;,
 -0.01938;-3.82327;-2.18347;,
 -1.84293;-3.24963;-2.17481;,
 -2.17720;-2.41202;-2.10312;,
 0.03122;-3.20643;-2.13286;,
 -2.88624;-2.40071;-1.87156;,
 -2.17720;-2.41202;-2.10312;,
 -1.84293;-3.24963;-2.17481;,
 -2.75803;-3.11136;-1.88056;,
 -3.60946;-2.93519;1.20653;,
 -2.58821;-3.06916;3.05540;,
 -2.61968;-4.17906;-2.07046;,
 -2.44425;-4.00937;-1.94094;,
 -2.75803;-3.11136;-1.88056;,
 -3.60946;-2.93519;1.20653;,
 -1.07642;-0.37228;1.08873;,
 -1.50659;-0.37013;1.11896;,
 -1.07642;-0.37228;1.08873;,
 1.02243;-4.62823;3.25099;,
 0.94232;-4.71683;0.91131;,
 1.97543;-4.72478;0.91554;,
 -2.12990;-4.61813;0.98936;,
 -0.04975;-4.68291;0.93897;,
 -0.09066;-4.81540;-1.55931;,
 -0.04958;-4.14234;-2.23506;,
 -1.27942;-4.65958;0.95072;,
 -2.13552;-4.72281;-1.36132;,
 -1.10005;-4.78955;-1.52328;,
 -1.39081;-4.78262;-1.50049;,
 3.66391;-1.05957;1.03088;,
 3.68020;-1.98365;1.03251;,
 1.33305;-2.91770;3.08814;,
 0.05590;-2.88187;3.16813;,
 2.79486;-2.96572;2.92802;,
 -0.01938;-3.82327;-2.18347;,
 -0.01938;-3.82327;-2.18347;,
 2.57271;-0.55003;-1.97962;,
 2.42793;-1.62531;-2.06476;,
 0.02992;-1.43202;-2.15244;,
 0.03963;-0.55334;-2.08311;,
 2.57271;-0.55003;-1.97962;,
 2.90910;-0.52274;-1.49258;,
 2.90910;-0.52274;-1.49258;,
 3.24100;-0.46555;-0.47825;,
 3.48213;-0.37760;1.07670;,
 -1.58660;-0.27178;2.85170;,
 0.36598;-2.29294;-2.14325;,
 -2.17720;-2.41202;-2.10312;,
 -2.17720;-2.41202;-2.10312;,
 -2.88624;-2.40071;-1.87156;,
 -2.44425;-4.00937;-1.94094;,
 -3.75111;-1.82716;1.17145;,
 -2.88624;-2.40071;-1.87156;;
 
 136;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 4;5,6,7,8;,
 4;9,10,11,12;,
 4;13,14,15,16;,
 4;17,18,19,20;,
 4;21,19,18,22;,
 4;23,24,25,26;,
 4;27,28,0,2;,
 4;29,30,31,32;,
 4;32,33,34,29;,
 4;35,36,37,38;,
 4;39,40,41,42;,
 4;43,44,45,46;,
 3;47,48,49;,
 3;48,50,49;,
 3;49,50,51;,
 3;50,52,51;,
 4;53,54,55,56;,
 4;57,55,54,58;,
 4;38,34,33,35;,
 3;1,5,3;,
 3;3,5,59;,
 3;5,8,59;,
 4;60,14,13,61;,
 4;62,63,64,65;,
 3;23,66,67;,
 3;66,68,67;,
 3;68,69,67;,
 4;70,24,23,67;,
 4;22,71,72,21;,
 4;58,73,74,57;,
 4;75,76,77,78;,
 4;79,76,75,80;,
 4;80,81,82,79;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 3;88,91,89;,
 4;92,93,94,95;,
 4;96,93,92,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,108,107,111;,
 4;8,7,112,59;,
 3;21,113,19;,
 4;72,114,113,21;,
 4;115,112,116,2;,
 4;117,118,61,13;,
 3;116,112,119;,
 3;112,117,119;,
 3;117,13,119;,
 3;13,16,119;,
 3;19,113,20;,
 4;80,75,120,121;,
 4;32,31,120,122;,
 4;123,124,125,126;,
 4;127,125,124,128;,
 4;129,130,36,35;,
 4;131,132,133,134;,
 4;135,136,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;147,148,149,150;,
 4;81,80,121,151;,
 4;26,25,16,15;,
 4;72,71,28,27;,
 4;30,74,73,31;,
 4;114,24,20,113;,
 3;152,73,58;,
 3;153,85,154;,
 3;154,85,155;,
 3;85,156,155;,
 4;157,27,2,116;,
 3;157,116,25;,
 3;116,119,25;,
 3;119,16,25;,
 4;25,24,158,159;,
 4;72,27,159,158;,
 4;160,161,162,102;,
 3;102,162,103;,
 3;82,163,79;,
 4;77,164,161,160;,
 4;165,91,88,166;,
 4;76,167,164,77;,
 4;76,79,163,167;,
 3;168,163,82;,
 3;163,168,167;,
 3;167,168,169;,
 3;168,170,169;,
 4;164,167,169,94;,
 4;161,164,94,93;,
 4;162,161,93,101;,
 4;103,162,101,100;,
 4;112,7,118,117;,
 4;11,10,7,6;,
 4;41,40,171,172;,
 4;130,133,132,36;,
 4;100,99,104,103;,
 4;122,120,75,78;,
 4;107,173,174,111;,
 4;175,173,107,106;,
 4;105,104,130,129;,
 4;99,133,130,104;,
 4;134,133,99,98;,
 4;97,92,136,135;,
 4;176,136,92,95;,
 4;88,149,177,166;,
 4;178,179,180,181;,
 4;65,64,182,183;,
 4;184,185,40,39;,
 4;171,40,185,186;,
 4;38,37,6,5;,
 4;5,1,34,38;,
 4;29,34,1,0;,
 3;187,29,0;,
 3;71,74,187;,
 4;57,74,71,22;,
 4;22,18,55,57;,
 4;56,55,18,17;,
 3;188,139,48;,
 3;48,139,50;,
 3;139,189,50;,
 4;190,191,69,68;,
 3;88,87,149;,
 3;149,87,192;,
 3;192,150,149;,
 3;152,121,73;,
 3;121,120,73;,
 3;120,31,73;,
 3;54,151,58;,
 3;151,121,58;,
 3;121,152,58;,
 4;155,156,193,194;,
 3;188,140,139;;
 
 MeshMaterialList {
  1;
  136;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\cat_color.jpg";
   }
  }
 }
 MeshNormals {
  145;
  -0.613210;-0.275222;0.740423;,
  0.010767;0.064902;0.997834;,
  0.623843;-0.311512;0.716785;,
  0.848711;-0.516797;0.112297;,
  0.575161;-0.553460;-0.602389;,
  -0.020819;-0.336707;-0.941379;,
  -0.467436;-0.791537;-0.393666;,
  -0.887975;-0.457410;0.047713;,
  0.001012;0.998395;-0.056630;,
  0.001014;0.998395;-0.056620;,
  0.001017;0.998395;-0.056625;,
  0.001012;0.998395;-0.056631;,
  0.001014;0.998395;-0.056631;,
  0.001012;0.998395;-0.056626;,
  0.001014;0.998395;-0.056631;,
  0.001010;0.998395;-0.056627;,
  0.001010;0.998395;-0.056626;,
  0.001011;0.998395;-0.056623;,
  0.001016;0.998396;-0.056615;,
  0.001019;0.998395;-0.056627;,
  0.001011;0.998395;-0.056629;,
  0.001015;0.998395;-0.056631;,
  0.001013;0.998395;-0.056625;,
  0.001012;0.998395;-0.056628;,
  0.153262;0.012942;0.988101;,
  0.001020;0.998395;-0.056628;,
  0.001016;0.998396;-0.056616;,
  0.001014;0.998395;-0.056629;,
  0.001011;0.998395;-0.056633;,
  0.065733;-0.382257;-0.921715;,
  -0.070892;-0.471514;-0.879005;,
  0.001017;0.998395;-0.056624;,
  0.001015;0.998395;-0.056626;,
  0.001014;0.998395;-0.056624;,
  0.001016;0.998395;-0.056626;,
  -0.157399;-0.017802;0.987375;,
  -0.000186;-0.001100;0.999999;,
  -0.197786;-0.058413;0.978503;,
  -0.641451;-0.330846;0.692157;,
  -0.531098;-0.842698;0.088290;,
  -0.210528;-0.977359;-0.021143;,
  -0.089630;-0.746763;-0.659023;,
  -0.028064;-0.934167;-0.355731;,
  0.008429;-0.933429;-0.358662;,
  0.280162;-0.939595;-0.196648;,
  0.534073;-0.841414;0.082395;,
  0.544844;-0.670353;0.503757;,
  0.183392;-0.064045;0.980951;,
  0.001018;0.998395;-0.056629;,
  0.001020;0.998395;-0.056617;,
  0.001016;0.998395;-0.056633;,
  0.001015;0.998395;-0.056631;,
  0.001016;0.998395;-0.056627;,
  0.001012;0.998395;-0.056632;,
  -0.697184;0.033234;0.716121;,
  -0.089439;0.096016;0.991353;,
  0.025589;0.117842;0.992703;,
  0.141843;0.147117;0.978896;,
  0.636018;0.079338;0.767585;,
  0.984458;-0.079394;0.156652;,
  0.697007;0.016309;-0.716878;,
  0.123146;0.059521;-0.990602;,
  -0.004064;0.006212;-0.999972;,
  -0.206536;-0.006075;-0.978420;,
  -0.750053;-0.024834;-0.660911;,
  -0.994202;-0.015701;0.106372;,
  -0.163398;0.163276;0.972955;,
  0.001020;0.998395;-0.056623;,
  0.001021;0.998395;-0.056627;,
  0.001017;0.998395;-0.056629;,
  0.001017;0.998395;-0.056624;,
  0.001014;0.998395;-0.056627;,
  0.986146;0.059452;-0.154862;,
  -0.689024;0.724561;-0.016044;,
  -0.212281;0.126196;0.969026;,
  -0.037958;-0.981891;-0.185604;,
  -0.129558;-0.990599;0.043905;,
  -0.040571;-0.998177;0.044681;,
  -0.025414;-0.998651;0.045289;,
  -0.015760;-0.998869;0.044860;,
  0.098469;-0.994083;0.045857;,
  0.001016;0.998395;-0.056628;,
  0.001010;0.998395;-0.056630;,
  0.001015;0.998395;-0.056630;,
  0.970292;-0.094073;-0.222897;,
  0.841427;-0.530073;-0.104993;,
  0.593008;-0.804755;-0.026657;,
  -0.116174;0.096306;0.988549;,
  0.023368;0.134559;0.990630;,
  0.122723;0.128923;0.984031;,
  0.628590;-0.094280;0.772002;,
  0.938167;-0.320190;0.131610;,
  0.930949;-0.328921;-0.158574;,
  0.921797;-0.310831;-0.231678;,
  0.097237;0.028421;-0.994855;,
  -0.006796;0.095198;-0.995435;,
  -0.144460;0.011165;-0.989448;,
  0.011709;0.053613;-0.998493;,
  0.290306;0.092968;-0.952407;,
  0.756334;0.150505;-0.636637;,
  0.950174;0.149525;-0.273516;,
  0.972820;0.158330;0.168974;,
  0.619773;0.223285;0.752346;,
  0.187752;0.190379;0.963590;,
  0.036992;0.103248;0.993968;,
  -0.314497;0.182304;0.931588;,
  -0.680963;0.212565;0.700790;,
  -0.971759;0.204574;0.117614;,
  -0.779856;0.200698;-0.592913;,
  -0.186101;0.111924;-0.976135;,
  -0.710234;-0.177922;-0.681110;,
  -0.576055;-0.106036;0.810504;,
  -0.953416;-0.239321;0.183639;,
  0.010976;0.004069;-0.999931;,
  -0.073581;0.110442;0.991155;,
  0.000792;0.077466;-0.996995;,
  -0.015453;0.148518;-0.988789;,
  -0.420006;0.279171;-0.863515;,
  -0.838182;0.094296;-0.537177;,
  -0.811597;0.215547;-0.543001;,
  -0.890145;-0.112356;-0.441608;,
  0.208478;-0.045611;-0.976963;,
  -0.600725;0.773946;-0.200341;,
  -0.926674;-0.309448;-0.213347;,
  -0.016232;-0.999061;0.040164;,
  -0.000077;-0.999131;0.041681;,
  -0.132762;-0.990198;0.043376;,
  -0.025366;-0.998945;0.038287;,
  -0.039218;-0.998463;0.039167;,
  0.015045;-0.886919;0.461679;,
  0.381623;0.078920;-0.920943;,
  0.811005;0.127292;-0.571023;,
  0.937163;0.210677;-0.278103;,
  0.944977;0.280747;0.167927;,
  0.600615;0.337787;0.724680;,
  0.213893;0.254504;0.943121;,
  0.047898;0.109335;0.992850;,
  -0.353491;0.276626;0.893601;,
  -0.691609;0.287963;0.662386;,
  -0.945041;0.303143;0.122478;,
  -0.093944;-0.033196;-0.995024;,
  -0.746867;0.643150;0.168961;,
  -0.311985;-0.045198;-0.949011;,
  -0.183580;-0.104191;-0.977467;,
  0.873646;0.168663;-0.456395;;
  136;
  3;17,25,10;,
  3;25,49,10;,
  3;49,26,10;,
  4;18,19,8,9;,
  4;15,82,83,20;,
  4;27,28,21,14;,
  4;22,23,12,13;,
  4;11,12,23,16;,
  4;31,32,69,68;,
  4;33,34,17,10;,
  4;104,114,55,56;,
  4;56,57,103,104;,
  4;58,59,101,102;,
  4;99,100,84,60;,
  4;97,98,61,113;,
  3;115,97,116;,
  3;97,109,116;,
  3;116,109,117;,
  3;72,72,72;,
  4;64,65,107,108;,
  4;106,107,65,54;,
  4;102,103,57,58;,
  3;25,18,49;,
  3;49,18,26;,
  3;18,9,26;,
  4;20,28,27,15;,
  4;60,61,98,99;,
  3;117,118,119;,
  3;118,120,119;,
  3;109,108,119;,
  4;13,32,31,22;,
  4;16,67,70,11;,
  4;54,74,105,106;,
  4;35,37,36,1;,
  4;38,37,35,0;,
  4;0,7,39,38;,
  4;40,39,7,6;,
  4;6,30,41,40;,
  3;30,75,41;,
  4;29,43,42,5;,
  4;44,43,29,4;,
  4;4,85,86,44;,
  4;46,45,3,2;,
  4;2,24,47,46;,
  4;36,47,24,1;,
  4;9,8,50,26;,
  3;11,53,12;,
  4;70,71,53,11;,
  4;26,50,51,10;,
  4;81,82,15,27;,
  3;51,50,48;,
  3;50,81,48;,
  3;81,27,48;,
  3;27,14,48;,
  3;12,53,13;,
  4;0,35,87,111;,
  4;56,55,87,88;,
  4;88,89,57,56;,
  4;58,57,89,90;,
  4;90,91,59,58;,
  4;60,84,92,93;,
  4;121,94,61,60;,
  4;62,61,94,95;,
  4;95,96,63,62;,
  4;64,63,96,110;,
  4;7,0,111,112;,
  4;68,69,14,21;,
  4;70,67,34,33;,
  4;114,105,74,55;,
  4;71,32,13,53;,
  3;66,74,54;,
  3;73,122,73;,
  3;123,7,123;,
  3;7,112,110;,
  4;52,33,10,51;,
  3;52,51,69;,
  3;51,48,69;,
  3;48,14,69;,
  4;69,32,71,52;,
  4;70,33,52,71;,
  4;124,79,80,125;,
  3;46,80,45;,
  3;39,76,126;,
  4;127,78,79,124;,
  4;42,75,30,5;,
  4;128,77,78,127;,
  4;128,126,76,77;,
  3;40,76,39;,
  3;76,40,77;,
  3;77,40,75;,
  3;40,129,75;,
  4;78,77,75,42;,
  4;79,78,42,43;,
  4;80,79,43,44;,
  4;45,80,44,86;,
  4;50,8,82,81;,
  4;83,82,8,19;,
  4;84,100,101,59;,
  4;91,92,84,59;,
  4;86,85,3,45;,
  4;88,87,35,1;,
  4;24,89,88,1;,
  4;90,89,24,2;,
  4;2,3,91,90;,
  4;85,92,91,3;,
  4;93,92,85,4;,
  4;4,29,94,121;,
  4;95,94,29,5;,
  4;30,96,95,5;,
  4;130,98,97,115;,
  4;99,98,130,131;,
  4;131,132,100,99;,
  4;101,100,132,133;,
  4;102,101,133,134;,
  4;134,135,103,102;,
  4;104,103,135,136;,
  3;114,104,136;,
  3;137,105,114;,
  4;106,105,137,138;,
  4;138,139,107,106;,
  4;108,107,139,119;,
  3;113,62,97;,
  3;97,62,109;,
  3;62,63,109;,
  4;63,64,108,109;,
  3;30,140,96;,
  3;141,73,73;,
  3;142,110,96;,
  3;143,143,143;,
  3;111,87,74;,
  3;87,55,74;,
  3;65,112,54;,
  3;112,111,54;,
  3;144,144,144;,
  4;110,112,65,64;,
  3;113,61,62;;
 }
 MeshTextureCoords {
  195;
  0.501700;0.951560;,
  0.517940;0.951560;,
  0.501700;0.947570;,
  0.517940;0.948860;,
  0.517940;0.947570;,
  0.538030;0.951560;,
  0.577150;0.951560;,
  0.577150;0.947570;,
  0.538030;0.947570;,
  0.614080;0.947570;,
  0.598630;0.947570;,
  0.598630;0.951560;,
  0.614080;0.951560;,
  0.517940;0.783600;,
  0.517940;0.822410;,
  0.501700;0.822410;,
  0.501700;0.783600;,
  0.385920;0.951560;,
  0.422850;0.951560;,
  0.422850;0.947570;,
  0.385920;0.947570;,
  0.461980;0.947570;,
  0.461980;0.951560;,
  0.479530;0.822410;,
  0.479530;0.783600;,
  0.480740;0.783600;,
  0.487370;0.822410;,
  0.479530;0.947570;,
  0.479530;0.951560;,
  0.501700;0.953620;,
  0.479530;0.953620;,
  0.479530;0.955020;,
  0.501700;0.955020;,
  0.517940;0.955020;,
  0.517940;0.953620;,
  0.538030;0.955020;,
  0.577150;0.955020;,
  0.577150;0.953620;,
  0.538030;0.953620;,
  0.614080;0.250940;,
  0.598630;0.250940;,
  0.598630;0.252330;,
  0.614080;0.252330;,
  0.653430;0.105880;,
  0.675530;0.105880;,
  0.675530;0.103980;,
  0.653430;0.104800;,
  0.653430;0.900960;,
  0.653430;0.898150;,
  0.633920;0.900960;,
  0.623260;0.898110;,
  0.623260;0.900960;,
  0.623260;0.898750;,
  0.385920;0.955020;,
  0.422850;0.955020;,
  0.422850;0.953620;,
  0.385920;0.953620;,
  0.461980;0.953620;,
  0.461980;0.955020;,
  0.519940;0.947570;,
  0.538030;0.779610;,
  0.538030;0.783600;,
  0.538030;0.073470;,
  0.517940;0.116270;,
  0.517940;0.117670;,
  0.538030;0.074860;,
  0.479530;0.820790;,
  0.461980;0.779610;,
  0.479530;0.820320;,
  0.461980;0.777550;,
  0.461980;0.783600;,
  0.478050;0.951560;,
  0.470950;0.947570;,
  0.466770;0.955020;,
  0.471320;0.953620;,
  0.479530;0.958090;,
  0.479530;0.962560;,
  0.501700;0.962560;,
  0.501700;0.958090;,
  0.461980;0.962560;,
  0.461980;0.958090;,
  0.422850;0.958090;,
  0.422850;0.962560;,
  0.385920;0.470310;,
  0.422850;0.470310;,
  0.422850;0.465830;,
  0.386590;0.465830;,
  0.461980;0.380900;,
  0.479530;0.380900;,
  0.479530;0.376420;,
  0.461980;0.376420;,
  0.484500;0.376420;,
  0.517940;0.773090;,
  0.517940;0.768610;,
  0.501700;0.768610;,
  0.501700;0.773090;,
  0.538030;0.768610;,
  0.538030;0.773090;,
  0.614080;0.958090;,
  0.598630;0.958090;,
  0.598630;0.962560;,
  0.614080;0.962560;,
  0.538030;0.962560;,
  0.577150;0.962560;,
  0.577150;0.958090;,
  0.538030;0.958090;,
  0.538030;0.166490;,
  0.517940;0.166490;,
  0.517940;0.170960;,
  0.538030;0.170960;,
  0.501700;0.170960;,
  0.501700;0.166490;,
  0.519390;0.901990;,
  0.444360;0.947570;,
  0.464910;0.920180;,
  0.518940;0.947570;,
  0.505920;0.901420;,
  0.518550;0.833130;,
  0.554390;0.852200;,
  0.513010;0.823810;,
  0.479530;0.957260;,
  0.461980;0.957080;,
  0.501700;0.957260;,
  0.501700;0.192270;,
  0.517940;0.192270;,
  0.517940;0.190030;,
  0.501700;0.190030;,
  0.538030;0.190030;,
  0.538030;0.192270;,
  0.538030;0.957260;,
  0.577150;0.957260;,
  0.614080;0.955020;,
  0.598630;0.955020;,
  0.598630;0.957260;,
  0.614080;0.957260;,
  0.538030;0.773910;,
  0.517940;0.816720;,
  0.517940;0.818960;,
  0.538030;0.776160;,
  0.653430;0.896260;,
  0.675530;0.896260;,
  0.675530;0.893200;,
  0.653430;0.893200;,
  0.653430;0.501010;,
  0.623260;0.501010;,
  0.623260;0.504070;,
  0.653430;0.504070;,
  0.461980;0.383970;,
  0.475710;0.405370;,
  0.479530;0.424530;,
  0.461980;0.382180;,
  0.422850;0.956990;,
  0.461980;0.956550;,
  0.387260;0.465830;,
  0.385920;0.465710;,
  0.385920;0.464540;,
  0.422850;0.464730;,
  0.479890;0.901940;,
  0.466590;0.917950;,
  0.479230;0.901950;,
  0.517940;0.962560;,
  0.517940;0.876380;,
  0.571660;0.962560;,
  0.461980;0.876730;,
  0.501700;0.877520;,
  0.501700;0.376420;,
  0.501700;0.380900;,
  0.481730;0.876780;,
  0.461980;0.768610;,
  0.484500;0.768610;,
  0.479530;0.768610;,
  0.577150;0.250940;,
  0.577150;0.252330;,
  0.517940;0.165660;,
  0.501700;0.165660;,
  0.538030;0.165660;,
  0.501700;0.816720;,
  0.501700;0.424530;,
  0.675530;0.198270;,
  0.675530;0.195460;,
  0.653430;0.195460;,
  0.653430;0.198270;,
  0.517940;0.119730;,
  0.538030;0.076920;,
  0.614080;0.248880;,
  0.598630;0.248880;,
  0.577150;0.248880;,
  0.479530;0.952590;,
  0.653430;0.897080;,
  0.623260;0.896260;,
  0.475710;0.797560;,
  0.461980;0.776160;,
  0.461980;0.381020;,
  0.422850;0.462760;,
  0.385920;0.462760;;
 }
}
