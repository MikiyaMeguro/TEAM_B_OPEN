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
 186;
 -0.57841;-2.50757;-3.67615;,
 -0.61505;-1.24609;-3.92187;,
 0.97832;-1.22577;-3.92141;,
 0.82708;-2.48964;-3.67575;,
 -0.54787;-2.21348;1.32236;,
 -0.58899;-2.34338;0.66232;,
 0.53843;-2.32900;0.66264;,
 0.49362;-2.20019;1.32267;,
 -0.56908;-1.75199;1.49771;,
 0.61161;-1.73694;1.49805;,
 -0.61592;-0.23813;0.79576;,
 -0.57093;-0.40813;1.44637;,
 0.47055;-0.39482;1.44666;,
 0.51153;-0.22376;0.79608;,
 1.28164;-2.21203;0.61023;,
 1.61323;-1.65539;0.76512;,
 1.27507;-1.71198;1.32241;,
 1.12935;-2.04674;1.16830;,
 -1.50154;-0.91170;1.45840;,
 -1.71578;-0.93705;0.72226;,
 -1.36031;-2.24575;0.60948;,
 -1.21261;-2.07662;1.16763;,
 -0.60809;-0.18279;-3.58281;,
 0.79739;-0.16484;-3.58242;,
 1.25745;-0.31821;0.73702;,
 1.10986;-0.52204;1.28349;,
 -1.23208;-0.55191;1.28280;,
 -1.38451;-0.35192;0.73626;,
 -0.63524;-2.62147;-2.74692;,
 0.88627;-2.60205;-2.74648;,
 1.88951;-2.46728;-2.68676;,
 2.33184;-1.30400;-2.90267;,
 1.86111;-0.24383;-2.59522;,
 -0.66680;-0.14927;-2.65090;,
 0.85469;-0.12985;-2.65048;,
 -1.70425;-0.28931;-2.59627;,
 -2.15139;-1.06368;-2.97726;,
 -1.67586;-2.51279;-2.68778;,
 1.87409;-1.23659;-3.68388;,
 1.68526;-2.30993;-3.48312;,
 1.66008;-0.33866;-3.39615;,
 -0.60809;-0.18279;-3.58281;,
 0.79739;-0.16484;-3.58242;,
 -1.50042;-0.37898;-3.39706;,
 -1.69401;-1.06481;-3.75968;,
 -1.47524;-2.35026;-3.48403;,
 -1.70425;-0.28931;-2.59627;,
 -1.50042;-0.37898;-3.39706;,
 -1.38451;-0.35192;0.73626;,
 -1.23208;-0.55191;1.28280;,
 -1.50154;-0.91170;1.45840;,
 -1.21261;-2.07662;1.16763;,
 -1.36031;-2.24575;0.60948;,
 -1.67586;-2.51279;-2.68778;,
 1.27507;-1.71198;1.32241;,
 1.10986;-0.52204;1.28349;,
 1.25745;-0.31821;0.73702;,
 1.86111;-0.24383;-2.59522;,
 1.66008;-0.33866;-3.39615;,
 1.88951;-2.46728;-2.68676;,
 1.28164;-2.21203;0.61023;,
 1.12935;-2.04674;1.16830;,
 0.60174;-2.35058;-5.32533;,
 0.46530;-1.30065;-5.39541;,
 0.99602;-1.24606;-5.43739;,
 1.06987;-2.30241;-5.36236;,
 0.89371;-2.46782;-2.72232;,
 0.82162;-2.49324;-3.31500;,
 1.27264;-2.44684;-3.35068;,
 1.31033;-2.42496;-2.75529;,
 0.80589;-1.56167;-2.47270;,
 1.27820;-1.51308;-2.51005;,
 0.60637;-0.48106;-3.11149;,
 0.69488;-0.60907;-2.53432;,
 1.11150;-0.56622;-2.56728;,
 1.05740;-0.43467;-3.14717;,
 1.55760;-2.33554;-3.41006;,
 1.60911;-1.41293;-3.19235;,
 1.52687;-1.47165;-2.68707;,
 1.53982;-2.28120;-2.89730;,
 0.43722;-1.59961;-2.44352;,
 0.28129;-1.54955;-3.08728;,
 0.50070;-2.44427;-3.32643;,
 0.60296;-2.37758;-2.82320;,
 0.37834;-0.26201;-5.11409;,
 0.84646;-0.21384;-5.15112;,
 1.35876;-0.47679;-3.22207;,
 1.36356;-0.63350;-2.73066;,
 0.42671;-0.72989;-2.65654;,
 0.30190;-0.58551;-3.13845;,
 0.66484;-2.50032;-4.65240;,
 1.17163;-2.44818;-4.69250;,
 1.50234;-2.33198;-4.66131;,
 1.52753;-1.26780;-4.72073;,
 1.27892;-0.24342;-4.45008;,
 0.42298;-0.23936;-4.42373;,
 0.92976;-0.18721;-4.46381;,
 0.09139;-0.36561;-4.35612;,
 0.03551;-1.42131;-4.60266;,
 0.31480;-2.45416;-4.56736;,
 1.31320;-1.23121;-5.28569;,
 1.35980;-2.16781;-5.22411;,
 1.16174;-0.31641;-5.03688;,
 0.37834;-0.26201;-5.11409;,
 0.84646;-0.21384;-5.15112;,
 0.10905;-0.42472;-4.95361;,
 0.12563;-1.35340;-5.19175;,
 0.30710;-2.27613;-5.14084;,
 0.09139;-0.36561;-4.35612;,
 0.10905;-0.42472;-4.95361;,
 0.30190;-0.58551;-3.13845;,
 0.42671;-0.72989;-2.65654;,
 0.43722;-1.59961;-2.44352;,
 0.60296;-2.37758;-2.82320;,
 0.50070;-2.44427;-3.32643;,
 0.31480;-2.45416;-4.56736;,
 1.52687;-1.47165;-2.68707;,
 1.36356;-0.63350;-2.73066;,
 1.35876;-0.47679;-3.22207;,
 1.27892;-0.24342;-4.45008;,
 1.16174;-0.31641;-5.03688;,
 1.50234;-2.33198;-4.66131;,
 1.55760;-2.33554;-3.41006;,
 1.53982;-2.28120;-2.89730;,
 -1.13880;-2.33438;-5.28512;,
 -1.21372;-1.27969;-5.37370;,
 -0.68092;-1.25710;-5.41856;,
 -0.66882;-2.31446;-5.32469;,
 -0.84213;-2.42209;-2.68147;,
 -0.91835;-2.45381;-3.27334;,
 -0.46556;-2.43460;-3.31148;,
 -0.42387;-2.40436;-2.71670;,
 -0.87552;-1.50804;-2.44799;,
 -0.40134;-1.48792;-2.48790;,
 -1.01426;-0.42915;-3.10552;,
 -0.93075;-0.55182;-2.52643;,
 -0.51248;-0.53407;-2.56167;,
 -0.56148;-0.40995;-3.14364;,
 -0.17486;-2.34130;-3.37388;,
 -0.06828;-1.41959;-3.17305;,
 -0.15148;-1.46433;-2.66654;,
 -0.18701;-2.27686;-2.86213;,
 -1.24564;-1.52373;-2.41681;,
 -1.40133;-1.47612;-3.06080;,
 -1.23587;-2.38628;-3.28452;,
 -1.12755;-2.31675;-2.78294;,
 -1.23835;-0.23287;-5.11090;,
 -0.76838;-0.21294;-5.15048;,
 -0.26344;-0.47102;-3.21885;,
 -0.26558;-0.61896;-2.72469;,
 -1.20611;-0.65885;-2.64548;,
 -1.32447;-0.51601;-3.12949;,
 -1.08145;-2.47553;-4.60984;,
 -0.57268;-2.45397;-4.65267;,
 -0.23557;-2.35685;-4.62479;,
 -0.14830;-1.29719;-4.70353;,
 -0.33513;-0.25532;-4.45058;,
 -1.18923;-0.20057;-4.42123;,
 -0.68047;-0.17898;-4.46408;,
 -1.52736;-0.30588;-4.35017;,
 -1.64618;-1.36072;-4.57738;,
 -1.42780;-2.40740;-4.52438;,
 -0.36274;-1.25820;-5.26831;,
 -0.37085;-2.19468;-5.18996;,
 -0.45911;-0.33178;-5.03554;,
 -1.23835;-0.23287;-5.11090;,
 -0.76838;-0.21294;-5.15048;,
 -1.51596;-0.37660;-4.94653;,
 -1.55495;-1.30877;-5.16792;,
 -1.42770;-2.23949;-5.10095;,
 -1.52736;-0.30588;-4.35017;,
 -1.51596;-0.37660;-4.94653;,
 -1.32447;-0.51601;-3.12949;,
 -1.20611;-0.65885;-2.64548;,
 -1.24564;-1.52373;-2.41681;,
 -1.12755;-2.31675;-2.78294;,
 -1.23587;-2.38628;-3.28452;,
 -1.42780;-2.40740;-4.52438;,
 -0.15148;-1.46433;-2.66654;,
 -0.26558;-0.61896;-2.72469;,
 -0.26344;-0.47102;-3.21885;,
 -0.33513;-0.25532;-4.45058;,
 -0.45911;-0.33178;-5.03554;,
 -0.23557;-2.35685;-4.62479;,
 -0.17486;-2.34130;-3.37388;,
 -0.18701;-2.27686;-2.86213;;
 
 126;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,4,7,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;1,22,23,2;,
 4;15,24,25,16;,
 4;11,8,9,12;,
 4;26,27,19,18;,
 4;5,28,29,6;,
 4;30,31,15,14;,
 4;31,32,24,15;,
 4;33,10,13,34;,
 4;19,27,35,36;,
 4;20,19,36,37;,
 4;28,0,3,29;,
 4;38,31,30,39;,
 4;40,32,31,38;,
 4;41,33,34,42;,
 4;36,35,43,44;,
 4;37,36,44,45;,
 4;46,33,41,47;,
 4;48,10,33,46;,
 4;49,11,10,48;,
 4;50,8,11,49;,
 4;51,4,8,50;,
 4;52,5,4,51;,
 4;53,28,5,52;,
 4;45,0,28,53;,
 4;44,1,0,45;,
 4;43,22,1,44;,
 4;12,9,54,55;,
 4;13,12,55,56;,
 4;34,13,56,57;,
 4;42,34,57,58;,
 4;2,23,40,38;,
 4;3,2,38,39;,
 4;29,3,39,59;,
 4;6,29,59,60;,
 4;7,6,60,61;,
 4;9,7,61,54;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,66,69,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;63,84,85,64;,
 4;77,86,87,78;,
 4;73,70,71,74;,
 4;88,89,81,80;,
 4;67,90,91,68;,
 4;92,93,77,76;,
 4;93,94,86,77;,
 4;95,72,75,96;,
 4;81,89,97,98;,
 4;82,81,98,99;,
 4;90,62,65,91;,
 4;100,93,92,101;,
 4;102,94,93,100;,
 4;103,95,96,104;,
 4;98,97,105,106;,
 4;99,98,106,107;,
 4;108,95,103,109;,
 4;110,72,95,108;,
 4;111,73,72,110;,
 4;112,70,73,111;,
 4;113,66,70,112;,
 4;114,67,66,113;,
 4;115,90,67,114;,
 4;107,62,90,115;,
 4;106,63,62,107;,
 4;105,84,63,106;,
 4;74,71,116,117;,
 4;75,74,117,118;,
 4;96,75,118,119;,
 4;104,96,119,120;,
 4;64,85,102,100;,
 4;65,64,100,101;,
 4;91,65,101,121;,
 4;68,91,121,122;,
 4;69,68,122,123;,
 4;71,69,123,116;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,128,131,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;142,143,144,145;,
 4;125,146,147,126;,
 4;139,148,149,140;,
 4;135,132,133,136;,
 4;150,151,143,142;,
 4;129,152,153,130;,
 4;154,155,139,138;,
 4;155,156,148,139;,
 4;157,134,137,158;,
 4;143,151,159,160;,
 4;144,143,160,161;,
 4;152,124,127,153;,
 4;162,155,154,163;,
 4;164,156,155,162;,
 4;165,157,158,166;,
 4;160,159,167,168;,
 4;161,160,168,169;,
 4;170,157,165,171;,
 4;172,134,157,170;,
 4;173,135,134,172;,
 4;174,132,135,173;,
 4;175,128,132,174;,
 4;176,129,128,175;,
 4;177,152,129,176;,
 4;169,124,152,177;,
 4;168,125,124,169;,
 4;167,146,125,168;,
 4;136,133,178,179;,
 4;137,136,179,180;,
 4;158,137,180,181;,
 4;166,158,181,182;,
 4;126,147,164,162;,
 4;127,126,162,163;,
 4;153,127,163,183;,
 4;130,153,183,184;,
 4;131,130,184,185;,
 4;133,131,185,178;;
 
 MeshMaterialList {
  1;
  126;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\rabbit_color.jpg";
   }
  }
 }
 MeshNormals {
  182;
  -0.431736;0.731293;-0.528029;,
  0.496876;0.680175;-0.538958;,
  -0.598620;-0.285823;-0.748304;,
  0.517960;-0.598836;-0.610830;,
  -0.547844;-0.610508;0.571968;,
  0.456562;-0.700854;0.548046;,
  -0.529040;0.783333;0.326352;,
  0.624223;0.141723;0.768284;,
  -0.605391;0.118642;-0.787036;,
  0.643020;0.060756;-0.763436;,
  0.620546;-0.207309;0.756271;,
  -0.799528;-0.023972;0.600150;,
  -0.935972;-0.282959;0.209500;,
  0.554046;-0.794443;0.248783;,
  0.939458;-0.126757;0.318357;,
  0.633165;0.715850;0.294383;,
  -0.552658;0.808616;0.201768;,
  -0.967017;0.128185;0.220105;,
  -0.943097;-0.299972;-0.143474;,
  0.608050;-0.787912;-0.097318;,
  0.992973;-0.011947;-0.117738;,
  0.751177;0.652065;-0.102689;,
  -0.551740;0.828712;-0.093907;,
  -0.981037;0.117684;-0.154001;,
  -0.079875;0.348549;-0.933881;,
  -0.087428;0.995975;-0.019760;,
  -0.096604;0.982450;0.159562;,
  -0.114858;0.950418;0.288985;,
  -0.079179;-0.123118;0.989228;,
  -0.134428;-0.745173;0.653181;,
  -0.070857;-0.985130;0.156519;,
  -0.062040;-0.997511;-0.033525;,
  -0.104514;-0.203862;-0.973405;,
  -0.095943;0.075550;-0.992516;,
  0.138473;-0.181605;0.973573;,
  0.094165;0.952565;0.289401;,
  0.074402;0.983881;0.162611;,
  0.064705;0.997759;-0.017041;,
  0.126044;0.325329;-0.937163;,
  0.131966;0.061953;-0.989316;,
  0.128377;-0.205702;-0.970158;,
  0.090184;-0.995449;-0.030788;,
  0.098817;-0.982225;0.159592;,
  0.144227;-0.764024;0.628861;,
  -0.856366;0.125177;-0.500967;,
  0.624114;0.603039;-0.496816;,
  -0.821959;-0.202781;-0.532225;,
  0.719624;-0.355536;-0.596436;,
  -0.668720;-0.718348;0.191808;,
  0.867295;-0.129106;0.480761;,
  -0.649160;0.424167;0.631406;,
  0.716620;0.518470;0.466524;,
  -0.850905;-0.039425;-0.523838;,
  0.749524;0.143714;-0.646188;,
  0.862545;0.039368;0.504447;,
  -0.963353;-0.128196;0.235619;,
  -0.662701;-0.734491;0.146113;,
  0.998901;-0.039890;0.024622;,
  0.994141;0.100838;0.038918;,
  0.699047;0.699127;0.150184;,
  -0.977511;0.030716;0.208636;,
  -0.972766;-0.124983;0.195205;,
  -0.968588;-0.248491;0.009486;,
  0.983567;-0.020713;-0.179348;,
  0.978680;0.119987;-0.166697;,
  0.954241;0.258279;-0.150716;,
  -0.998799;0.031102;0.037864;,
  -0.993666;-0.109798;0.023915;,
  -0.337031;0.225248;-0.914152;,
  -0.243828;0.966038;0.085545;,
  -0.228377;0.943814;0.238871;,
  -0.251974;0.929001;0.271047;,
  -0.041183;-0.106786;0.993429;,
  -0.068053;-0.994748;0.076461;,
  -0.043066;-0.998160;0.042680;,
  -0.056863;-0.992123;-0.111615;,
  -0.304838;-0.108671;-0.946184;,
  -0.325589;0.059130;-0.943661;,
  0.349942;-0.058879;0.934919;,
  0.102006;0.966378;0.236025;,
  0.070531;0.975294;0.209349;,
  0.056876;0.996793;0.056295;,
  0.156654;0.285828;-0.945390;,
  0.175902;0.115990;-0.977551;,
  0.189829;-0.057372;-0.980139;,
  0.243686;-0.959540;-0.141069;,
  0.256040;-0.966563;0.014146;,
  0.286217;-0.957206;0.042857;,
  -0.849865;0.166273;-0.500083;,
  0.656085;0.556390;-0.509884;,
  -0.834893;-0.163625;-0.525529;,
  0.694753;-0.407774;-0.592484;,
  -0.708812;-0.674296;0.207148;,
  0.860459;-0.171213;0.479893;,
  -0.620232;0.472757;0.625950;,
  0.747952;0.483739;0.454494;,
  -0.854170;0.001262;-0.519992;,
  0.753654;0.087896;-0.651368;,
  0.865700;-0.002345;0.500557;,
  -0.968114;-0.067190;0.241329;,
  -0.703957;-0.691582;0.161740;,
  0.994944;-0.098044;0.021755;,
  0.998514;0.042963;0.033531;,
  0.739533;0.659441;0.135012;,
  -0.973054;0.091766;0.211531;,
  -0.977508;-0.064150;0.200905;,
  -0.981441;-0.190967;0.017447;,
  0.979820;-0.081630;-0.182456;,
  0.983251;0.059312;-0.172339;,
  0.967040;0.199057;-0.158779;,
  -0.995071;0.090352;0.040863;,
  -0.998274;-0.050819;0.029450;,
  -0.327480;0.228294;-0.916864;,
  -0.186347;0.980063;0.068926;,
  -0.171531;0.959708;0.222569;,
  -0.195822;0.946880;0.255092;,
  -0.042771;-0.086424;0.995340;,
  -0.125919;-0.987513;0.094674;,
  -0.101331;-0.992988;0.060877;,
  -0.115463;-0.988907;-0.093441;,
  -0.315065;-0.107456;-0.942967;,
  -0.325933;0.061292;-0.943404;,
  0.350222;-0.062617;0.934572;,
  0.159590;0.962783;0.218129;,
  0.128558;0.973054;0.191412;,
  0.115470;0.992582;0.038049;,
  0.168753;0.259217;-0.950962;,
  0.177856;0.087992;-0.980115;,
  0.181580;-0.085909;-0.979616;,
  0.186331;-0.974560;-0.124550;,
  0.198993;-0.979520;0.030709;,
  0.229808;-0.971438;0.059125;,
  -0.007236;0.103783;0.994574;,
  0.128649;0.052234;0.990314;,
  -0.072194;-0.985960;-0.150570;,
  0.100553;-0.983426;-0.150871;,
  -0.097986;0.992906;-0.067352;,
  0.075828;0.994821;-0.067686;,
  -0.013672;0.168935;0.985532;,
  -0.154067;-0.972441;0.174994;,
  -0.136780;-0.989489;-0.046927;,
  -0.156500;-0.971315;-0.179036;,
  0.199535;0.925640;0.321523;,
  0.119385;0.992003;0.040964;,
  -0.020742;-0.310487;0.950351;,
  0.361375;-0.231255;0.903288;,
  -0.059819;0.101553;0.993030;,
  0.327718;0.115294;0.937714;,
  -0.094904;-0.968182;-0.231553;,
  0.257752;-0.928690;-0.266644;,
  -0.279397;0.959426;-0.037929;,
  0.073745;0.994670;-0.072069;,
  -0.387378;0.917942;0.085568;,
  -0.445503;0.893951;-0.048772;,
  -0.368292;0.891898;0.262447;,
  -0.171910;-0.119544;0.977832;,
  -0.143398;-0.360304;0.921747;,
  -0.205752;-0.972982;-0.104748;,
  -0.269044;-0.934767;-0.232003;,
  0.208630;0.977608;0.027510;,
  0.389635;-0.906454;-0.162868;,
  0.403006;-0.915052;0.016333;,
  0.457930;-0.887327;0.054321;,
  -0.034521;-0.291703;0.955886;,
  0.351382;-0.235899;0.906026;,
  -0.049149;0.122602;0.991238;,
  0.338261;0.112578;0.934294;,
  -0.152589;-0.964920;-0.213651;,
  0.201587;-0.946840;-0.250712;,
  -0.222815;0.973349;-0.054276;,
  0.131594;0.987181;-0.090313;,
  -0.332443;0.940497;0.070331;,
  -0.392507;0.917565;-0.063343;,
  -0.314104;0.916537;0.247584;,
  -0.174096;-0.091762;0.980444;,
  -0.160032;-0.334736;0.928623;,
  -0.262926;-0.960941;-0.086389;,
  -0.324450;-0.921358;-0.214081;,
  0.265696;0.964014;0.009071;,
  0.335045;-0.930534;-0.147824;,
  0.348739;-0.936692;0.031441;,
  0.405370;-0.911567;0.068709;;
  126;
  4;32,33,39,40;,
  4;29,30,42,43;,
  4;28,29,43,34;,
  4;26,27,35,36;,
  4;13,14,10,5;,
  4;11,17,12,4;,
  4;33,24,38,39;,
  4;14,15,7,10;,
  4;132,28,34,133;,
  4;6,16,17,11;,
  4;30,31,41,42;,
  4;19,20,14,13;,
  4;20,21,15,14;,
  4;25,26,36,37;,
  4;17,16,22,23;,
  4;12,17,23,18;,
  4;31,134,135,41;,
  4;9,20,19,3;,
  4;1,21,20,9;,
  4;136,25,37,137;,
  4;23,22,0,8;,
  4;18,23,8,2;,
  4;22,25,136,0;,
  4;16,26,25,22;,
  4;6,27,26,16;,
  4;138,28,132,138;,
  4;4,29,28,11;,
  4;139,30,29,4;,
  4;140,31,30,139;,
  4;141,134,31,140;,
  4;8,33,32,2;,
  4;0,24,33,8;,
  4;133,34,10,7;,
  4;36,35,142,15;,
  4;37,36,15,143;,
  4;137,37,21,1;,
  4;39,38,1,9;,
  4;40,39,9,3;,
  4;41,135,3,19;,
  4;42,41,19,13;,
  4;43,42,13,5;,
  4;34,43,5,10;,
  4;76,77,83,84;,
  4;73,74,86,87;,
  4;72,144,145,78;,
  4;70,71,79,80;,
  4;57,58,54,49;,
  4;55,61,56,48;,
  4;77,68,82,83;,
  4;58,59,51,54;,
  4;146,72,78,147;,
  4;50,60,61,55;,
  4;74,75,85,86;,
  4;63,64,58,57;,
  4;64,65,59,58;,
  4;69,70,80,81;,
  4;61,60,66,67;,
  4;56,61,67,62;,
  4;75,148,149,85;,
  4;53,64,63,47;,
  4;45,65,64,53;,
  4;150,69,81,151;,
  4;67,66,44,52;,
  4;62,67,52,46;,
  4;152,69,150,153;,
  4;154,70,69,152;,
  4;50,71,70,154;,
  4;155,72,146,50;,
  4;156,144,72,155;,
  4;56,74,73,48;,
  4;157,75,74,56;,
  4;158,148,75,157;,
  4;52,77,76,46;,
  4;44,68,77,52;,
  4;147,78,54,51;,
  4;80,79,51,59;,
  4;81,80,59,159;,
  4;151,81,159,45;,
  4;83,82,45,53;,
  4;84,83,53,47;,
  4;85,149,47,160;,
  4;86,85,160,161;,
  4;87,86,161,162;,
  4;78,145,49,54;,
  4;120,121,127,128;,
  4;117,118,130,131;,
  4;116,163,164,122;,
  4;114,115,123,124;,
  4;101,102,98,93;,
  4;99,105,100,92;,
  4;121,112,126,127;,
  4;102,103,95,98;,
  4;165,116,122,166;,
  4;94,104,105,99;,
  4;118,119,129,130;,
  4;107,108,102,101;,
  4;108,109,103,102;,
  4;113,114,124,125;,
  4;105,104,110,111;,
  4;100,105,111,106;,
  4;119,167,168,129;,
  4;97,108,107,91;,
  4;89,109,108,97;,
  4;169,113,125,170;,
  4;111,110,88,96;,
  4;106,111,96,90;,
  4;171,113,169,172;,
  4;173,114,113,171;,
  4;94,115,114,173;,
  4;174,116,165,94;,
  4;175,163,116,174;,
  4;100,118,117,92;,
  4;176,119,118,100;,
  4;177,167,119,176;,
  4;96,121,120,90;,
  4;88,112,121,96;,
  4;166,122,98,95;,
  4;124,123,95,103;,
  4;125,124,103,178;,
  4;170,125,178,89;,
  4;127,126,89,97;,
  4;128,127,97,91;,
  4;129,168,91,179;,
  4;130,129,179,180;,
  4;131,130,180,181;,
  4;122,164,93,98;;
 }
 MeshTextureCoords {
  186;
  0.500273;0.173047;,
  0.500273;0.181160;,
  0.505375;0.181160;,
  0.505375;0.173047;,
  0.500273;0.156672;,
  0.500273;0.160560;,
  0.505375;0.160560;,
  0.505375;0.156672;,
  0.500273;0.148560;,
  0.505375;0.148560;,
  0.500273;0.136410;,
  0.500273;0.140298;,
  0.505375;0.140298;,
  0.505375;0.136410;,
  0.520675;0.173047;,
  0.520675;0.181160;,
  0.524562;0.181160;,
  0.524562;0.173047;,
  0.475438;0.181160;,
  0.479325;0.181160;,
  0.479325;0.173047;,
  0.475438;0.173047;,
  0.500273;0.189422;,
  0.505375;0.189422;,
  0.520675;0.189422;,
  0.524562;0.189422;,
  0.475438;0.189422;,
  0.479325;0.189422;,
  0.500273;0.168495;,
  0.505375;0.168495;,
  0.512739;0.173047;,
  0.512739;0.181160;,
  0.512739;0.189422;,
  0.500273;0.128475;,
  0.505375;0.128475;,
  0.487261;0.189422;,
  0.487261;0.181160;,
  0.487261;0.173047;,
  0.508187;0.181160;,
  0.508187;0.173047;,
  0.508187;0.189422;,
  0.500273;0.123923;,
  0.505375;0.123923;,
  0.491813;0.189422;,
  0.491813;0.181160;,
  0.491813;0.173047;,
  0.491813;0.128475;,
  0.491813;0.123923;,
  0.491813;0.136410;,
  0.491813;0.140298;,
  0.491813;0.148560;,
  0.491813;0.156672;,
  0.491813;0.160560;,
  0.491813;0.168495;,
  0.508187;0.148560;,
  0.508187;0.140298;,
  0.508187;0.136410;,
  0.508187;0.128475;,
  0.508187;0.123923;,
  0.508187;0.168495;,
  0.508187;0.160560;,
  0.508187;0.156672;,
  0.500273;0.173047;,
  0.500273;0.181160;,
  0.505375;0.181160;,
  0.505375;0.173047;,
  0.500273;0.156672;,
  0.500273;0.160560;,
  0.505375;0.160560;,
  0.505375;0.156672;,
  0.500273;0.148560;,
  0.505375;0.148560;,
  0.500273;0.136410;,
  0.500273;0.140298;,
  0.505375;0.140298;,
  0.505375;0.136410;,
  0.520675;0.173047;,
  0.520675;0.181160;,
  0.524562;0.181160;,
  0.524562;0.173047;,
  0.475438;0.181160;,
  0.479325;0.181160;,
  0.479325;0.173047;,
  0.475438;0.173047;,
  0.500273;0.189422;,
  0.505375;0.189422;,
  0.520675;0.189422;,
  0.524562;0.189422;,
  0.475438;0.189422;,
  0.479325;0.189422;,
  0.500273;0.168495;,
  0.505375;0.168495;,
  0.512739;0.173047;,
  0.512739;0.181160;,
  0.512739;0.189422;,
  0.500273;0.128475;,
  0.505375;0.128475;,
  0.487261;0.189422;,
  0.487261;0.181160;,
  0.487261;0.173047;,
  0.508187;0.181160;,
  0.508187;0.173047;,
  0.508187;0.189422;,
  0.500273;0.123923;,
  0.505375;0.123923;,
  0.491813;0.189422;,
  0.491813;0.181160;,
  0.491813;0.173047;,
  0.491813;0.128475;,
  0.491813;0.123923;,
  0.491813;0.136410;,
  0.491813;0.140298;,
  0.491813;0.148560;,
  0.491813;0.156672;,
  0.491813;0.160560;,
  0.491813;0.168495;,
  0.508187;0.148560;,
  0.508187;0.140298;,
  0.508187;0.136410;,
  0.508187;0.128475;,
  0.508187;0.123923;,
  0.508187;0.168495;,
  0.508187;0.160560;,
  0.508187;0.156672;,
  0.500273;0.173047;,
  0.500273;0.181160;,
  0.505375;0.181160;,
  0.505375;0.173047;,
  0.500273;0.156672;,
  0.500273;0.160560;,
  0.505375;0.160560;,
  0.505375;0.156672;,
  0.500273;0.148560;,
  0.505375;0.148560;,
  0.500273;0.136410;,
  0.500273;0.140298;,
  0.505375;0.140298;,
  0.505375;0.136410;,
  0.520675;0.173047;,
  0.520675;0.181160;,
  0.524562;0.181160;,
  0.524562;0.173047;,
  0.475438;0.181160;,
  0.479325;0.181160;,
  0.479325;0.173047;,
  0.475438;0.173047;,
  0.500273;0.189422;,
  0.505375;0.189422;,
  0.520675;0.189422;,
  0.524562;0.189422;,
  0.475438;0.189422;,
  0.479325;0.189422;,
  0.500273;0.168495;,
  0.505375;0.168495;,
  0.512739;0.173047;,
  0.512739;0.181160;,
  0.512739;0.189422;,
  0.500273;0.128475;,
  0.505375;0.128475;,
  0.487261;0.189422;,
  0.487261;0.181160;,
  0.487261;0.173047;,
  0.508187;0.181160;,
  0.508187;0.173047;,
  0.508187;0.189422;,
  0.500273;0.123923;,
  0.505375;0.123923;,
  0.491813;0.189422;,
  0.491813;0.181160;,
  0.491813;0.173047;,
  0.491813;0.128475;,
  0.491813;0.123923;,
  0.491813;0.136410;,
  0.491813;0.140298;,
  0.491813;0.148560;,
  0.491813;0.156672;,
  0.491813;0.160560;,
  0.491813;0.168495;,
  0.508187;0.148560;,
  0.508187;0.140298;,
  0.508187;0.136410;,
  0.508187;0.128475;,
  0.508187;0.123923;,
  0.508187;0.168495;,
  0.508187;0.160560;,
  0.508187;0.156672;;
 }
}
