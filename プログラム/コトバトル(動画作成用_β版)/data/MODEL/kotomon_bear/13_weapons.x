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
 182;
 -6.38291;-0.39287;-4.19806;,
 -6.46858;-0.56851;4.46601;,
 6.34109;-0.69695;4.59012;,
 6.42675;-0.52131;-4.07393;,
 6.24677;-10.79761;4.39898;,
 6.33246;-10.62196;-4.26507;,
 -6.56285;-10.66915;4.27485;,
 -6.47720;-10.49351;-4.38920;,
 -6.46858;-0.56851;4.46601;,
 -6.38291;-0.39287;-4.19806;,
 -6.56285;-10.66915;4.27485;,
 6.24677;-10.79761;4.39898;,
 -6.47720;-10.49351;-4.38920;,
 6.33246;-10.62196;-4.26507;,
 -3.41136;-7.65707;4.48824;,
 -2.85796;-7.56641;4.49462;,
 -3.96292;-7.55536;4.48505;,
 -2.35692;-7.29227;4.50476;,
 -4.45878;-7.27124;4.48661;,
 -1.95739;-6.86146;4.51681;,
 -4.85024;-6.83247;4.49101;,
 -1.69831;-6.31609;4.52965;,
 -5.09907;-6.28204;4.49894;,
 -1.60511;-5.70962;4.53976;,
 -5.18095;-5.67386;4.50957;,
 -1.68698;-5.10149;4.55261;,
 -5.08774;-5.06742;4.52192;,
 -1.93582;-4.55101;4.56055;,
 -4.82865;-4.52205;4.53476;,
 -2.32724;-4.11226;4.56495;,
 -4.42910;-4.09126;4.54680;,
 -2.82309;-3.82811;4.56540;,
 -3.92806;-3.81707;4.55580;,
 -3.37467;-3.72643;4.56262;,
 -1.69831;-6.31609;4.52965;,
 -1.95739;-6.86146;4.51681;,
 -3.60700;-5.68295;4.19584;,
 -2.35692;-7.29227;4.50476;,
 -2.85796;-7.56641;4.49462;,
 -3.41136;-7.65707;4.48824;,
 -3.96292;-7.55536;4.48505;,
 -4.45878;-7.27124;4.48661;,
 -4.85024;-6.83247;4.49101;,
 -5.09907;-6.28204;4.49894;,
 -5.18095;-5.67386;4.50957;,
 -5.08774;-5.06742;4.52192;,
 -4.82865;-4.52205;4.53476;,
 -4.42910;-4.09126;4.54680;,
 -3.92806;-3.81707;4.55580;,
 -3.37467;-3.72643;4.56262;,
 -2.82309;-3.82811;4.56540;,
 -2.32724;-4.11226;4.56495;,
 -1.93582;-4.55101;4.56055;,
 -1.68698;-5.10149;4.55261;,
 -1.60511;-5.70962;4.53976;,
 -1.69831;-6.31609;4.52965;,
 -3.49584;-8.10737;4.41231;,
 -2.81122;-7.99521;4.41992;,
 -4.17827;-7.98155;4.40853;,
 -2.19139;-7.65603;4.43243;,
 -4.79169;-7.63007;4.41091;,
 -1.69703;-7.12305;4.44735;,
 -5.27595;-7.08724;4.41637;,
 -1.37652;-6.44837;4.46321;,
 -5.58383;-6.40625;4.42615;,
 -1.26123;-5.69803;4.47480;,
 -5.68510;-5.65383;4.43932;,
 -1.36248;-4.94568;4.49167;,
 -5.56983;-4.90357;4.45459;,
 -1.67035;-4.26466;4.50145;,
 -5.24930;-4.22885;4.47047;,
 -2.15465;-3.72185;4.50688;,
 -4.75498;-3.69589;4.48537;,
 -2.76805;-3.37033;4.50744;,
 -4.13512;-3.35664;4.49606;,
 -3.45043;-3.24453;4.50433;,
 -1.37652;-6.44837;4.46321;,
 -1.69703;-7.12305;4.44735;,
 -3.49005;-5.66476;3.91760;,
 -2.19139;-7.65603;4.43243;,
 -2.81122;-7.99521;4.41992;,
 -3.49584;-8.10737;4.41231;,
 -4.17827;-7.98155;4.40853;,
 -4.79169;-7.63007;4.41091;,
 -5.27595;-7.08724;4.41637;,
 -5.58383;-6.40625;4.42615;,
 -5.68510;-5.65383;4.43932;,
 -5.56983;-4.90357;4.45459;,
 -5.24930;-4.22885;4.47047;,
 -4.75498;-3.69589;4.48537;,
 -4.13512;-3.35664;4.49606;,
 -3.45043;-3.24453;4.50433;,
 -2.76805;-3.37033;4.50744;,
 -2.15465;-3.72185;4.50688;,
 -1.67035;-4.26466;4.50145;,
 -1.36248;-4.94568;4.49167;,
 -1.26123;-5.69803;4.47480;,
 -1.37652;-6.44837;4.46321;,
 2.56667;-8.63013;4.52898;,
 3.39855;-8.49387;4.53860;,
 1.73746;-8.47726;4.52417;,
 4.15172;-8.08174;4.55380;,
 0.99213;-8.05015;4.52654;,
 4.75240;-7.43412;4.57194;,
 0.40370;-7.39055;4.53316;,
 5.14185;-6.61428;4.59122;,
 0.02957;-6.56309;4.54504;,
 5.28194;-5.70258;4.60642;,
 -0.09345;-5.64880;4.56106;,
 5.15890;-4.78836;4.62577;,
 0.04662;-4.73716;4.57959;,
 4.78484;-3.96088;4.63766;,
 0.43610;-3.91734;4.59888;,
 4.19637;-3.30133;4.64427;,
 1.03677;-3.26970;4.61700;,
 3.45101;-2.87418;4.64496;,
 1.78991;-2.85752;4.63055;,
 2.62181;-2.72130;4.64079;,
 5.14185;-6.61428;4.59122;,
 4.75240;-7.43412;4.57194;,
 2.27260;-5.66247;4.08941;,
 4.15172;-8.08174;4.55380;,
 3.39855;-8.49387;4.53860;,
 2.56667;-8.63013;4.52898;,
 1.73746;-8.47726;4.52417;,
 0.99213;-8.05015;4.52654;,
 0.40370;-7.39055;4.53316;,
 0.02957;-6.56309;4.54504;,
 -0.09345;-5.64880;4.56106;,
 0.04662;-4.73716;4.57959;,
 0.43610;-3.91734;4.59888;,
 1.03677;-3.26970;4.61700;,
 1.78991;-2.85752;4.63055;,
 2.62181;-2.72130;4.64079;,
 3.45101;-2.87418;4.64496;,
 4.19637;-3.30133;4.64427;,
 4.78484;-3.96088;4.63766;,
 5.15890;-4.78836;4.62577;,
 5.28194;-5.70258;4.60642;,
 5.14185;-6.61428;4.59122;,
 2.56646;-9.03096;4.46235;,
 3.51157;-8.87613;4.47330;,
 1.62446;-8.85726;4.45693;,
 4.36720;-8.40793;4.49057;,
 0.77770;-8.37204;4.45960;,
 5.04964;-7.67220;4.51117;,
 0.10919;-7.62273;4.46711;,
 5.49206;-6.74081;4.53308;,
 -0.31581;-6.68265;4.48063;,
 5.65121;-5.70506;4.55032;,
 -0.45556;-5.64398;4.49880;,
 5.51144;-4.66645;4.57234;,
 -0.29644;-4.60831;4.51988;,
 5.08646;-3.72638;4.58585;,
 0.14602;-3.67691;4.54179;,
 4.41790;-2.97707;4.59336;,
 0.82839;-2.94116;4.56238;,
 3.57118;-2.49179;4.59414;,
 1.68407;-2.47290;4.57775;,
 2.62915;-2.31813;4.58939;,
 5.49206;-6.74081;4.53308;,
 5.04964;-7.67220;4.51117;,
 2.57259;-5.66291;3.96631;,
 4.36720;-8.40793;4.49057;,
 3.51157;-8.87613;4.47330;,
 2.56646;-9.03096;4.46235;,
 1.62446;-8.85726;4.45693;,
 0.77770;-8.37204;4.45960;,
 0.10919;-7.62273;4.46711;,
 -0.31581;-6.68265;4.48063;,
 -0.45556;-5.64398;4.49880;,
 -0.29644;-4.60831;4.51988;,
 0.14602;-3.67691;4.54179;,
 0.82839;-2.94116;4.56238;,
 1.68407;-2.47290;4.57775;,
 2.62915;-2.31813;4.58939;,
 3.57118;-2.49179;4.59414;,
 4.41790;-2.97707;4.59336;,
 5.08646;-3.72638;4.58585;,
 5.51144;-4.66645;4.57234;,
 5.65121;-5.70506;4.55032;,
 5.49206;-6.74081;4.53308;;
 
 158;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 3;14,15,16;,
 3;15,17,16;,
 3;16,17,18;,
 3;17,19,18;,
 3;18,19,20;,
 3;19,21,20;,
 3;20,21,22;,
 3;21,23,22;,
 3;22,23,24;,
 3;23,25,24;,
 3;24,25,26;,
 3;25,27,26;,
 3;26,27,28;,
 3;27,29,28;,
 3;28,29,30;,
 3;29,31,30;,
 3;30,31,32;,
 3;31,33,32;,
 3;34,35,36;,
 3;35,37,36;,
 3;37,38,36;,
 3;38,39,36;,
 3;39,40,36;,
 3;40,41,36;,
 3;41,42,36;,
 3;42,43,36;,
 3;43,44,36;,
 3;44,45,36;,
 3;45,46,36;,
 3;46,47,36;,
 3;47,48,36;,
 3;48,49,36;,
 3;49,50,36;,
 3;50,51,36;,
 3;51,52,36;,
 3;52,53,36;,
 3;53,54,36;,
 3;54,55,36;,
 3;56,57,58;,
 3;57,59,58;,
 3;58,59,60;,
 3;59,61,60;,
 3;60,61,62;,
 3;61,63,62;,
 3;62,63,64;,
 3;63,65,64;,
 3;64,65,66;,
 3;65,67,66;,
 3;66,67,68;,
 3;67,69,68;,
 3;68,69,70;,
 3;69,71,70;,
 3;70,71,72;,
 3;71,73,72;,
 3;72,73,74;,
 3;73,75,74;,
 3;76,77,78;,
 3;77,79,78;,
 3;79,80,78;,
 3;80,81,78;,
 3;81,82,78;,
 3;82,83,78;,
 3;83,84,78;,
 3;84,85,78;,
 3;85,86,78;,
 3;86,87,78;,
 3;87,88,78;,
 3;88,89,78;,
 3;89,90,78;,
 3;90,91,78;,
 3;91,92,78;,
 3;92,93,78;,
 3;93,94,78;,
 3;94,95,78;,
 3;95,96,78;,
 3;96,97,78;,
 3;98,99,100;,
 3;99,101,100;,
 3;100,101,102;,
 3;101,103,102;,
 3;102,103,104;,
 3;103,105,104;,
 3;104,105,106;,
 3;105,107,106;,
 3;106,107,108;,
 3;107,109,108;,
 3;108,109,110;,
 3;109,111,110;,
 3;110,111,112;,
 3;111,113,112;,
 3;112,113,114;,
 3;113,115,114;,
 3;114,115,116;,
 3;115,117,116;,
 3;118,119,120;,
 3;119,121,120;,
 3;121,122,120;,
 3;122,123,120;,
 3;123,124,120;,
 3;124,125,120;,
 3;125,126,120;,
 3;126,127,120;,
 3;127,128,120;,
 3;128,129,120;,
 3;129,130,120;,
 3;130,131,120;,
 3;131,132,120;,
 3;132,133,120;,
 3;133,134,120;,
 3;134,135,120;,
 3;135,136,120;,
 3;136,137,120;,
 3;137,138,120;,
 3;138,139,120;,
 3;140,141,142;,
 3;141,143,142;,
 3;142,143,144;,
 3;143,145,144;,
 3;144,145,146;,
 3;145,147,146;,
 3;146,147,148;,
 3;147,149,148;,
 3;148,149,150;,
 3;149,151,150;,
 3;150,151,152;,
 3;151,153,152;,
 3;152,153,154;,
 3;153,155,154;,
 3;154,155,156;,
 3;155,157,156;,
 3;156,157,158;,
 3;157,159,158;,
 3;160,161,162;,
 3;161,163,162;,
 3;163,164,162;,
 3;164,165,162;,
 3;165,166,162;,
 3;166,167,162;,
 3;167,168,162;,
 3;168,169,162;,
 3;169,170,162;,
 3;170,171,162;,
 3;171,172,162;,
 3;172,173,162;,
 3;173,174,162;,
 3;174,175,162;,
 3;175,176,162;,
 3;176,177,162;,
 3;177,178,162;,
 3;178,179,162;,
 3;179,180,162;,
 3;180,181,162;;
 
 MeshMaterialList {
  1;
  158;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  170;
  0.009827;0.999744;0.020364;,
  0.999908;-0.009519;0.009694;,
  -0.009828;-0.999744;-0.020365;,
  -0.009167;-0.017682;0.999802;,
  -0.009012;-0.019042;0.999778;,
  -0.008846;-0.020489;0.999751;,
  -0.008840;-0.018639;0.999787;,
  -0.008819;-0.016479;0.999825;,
  -0.008842;-0.019396;0.999773;,
  -0.008924;-0.019606;0.999768;,
  -0.009139;-0.018645;0.999784;,
  -0.009007;-0.017489;0.999806;,
  -0.008834;-0.019955;0.999762;,
  -0.009176;-0.018909;0.999779;,
  -0.009009;-0.019036;0.999778;,
  -0.008827;-0.017781;0.999803;,
  -0.008877;-0.018790;0.999784;,
  -0.008898;-0.020961;0.999741;,
  -0.008851;-0.018181;0.999795;,
  -0.008907;-0.018286;0.999793;,
  -0.009136;-0.018640;0.999785;,
  -0.009028;-0.019935;0.999761;,
  -0.008824;-0.018729;0.999786;,
  -0.002147;0.018963;-0.999818;,
  -0.008929;-0.017261;0.999811;,
  -0.008719;-0.019117;0.999779;,
  -0.008503;-0.020993;0.999743;,
  -0.008519;-0.018642;0.999790;,
  -0.008493;-0.016026;0.999836;,
  -0.008509;-0.019627;0.999771;,
  -0.008599;-0.019885;0.999765;,
  -0.008891;-0.018547;0.999788;,
  -0.008715;-0.017036;0.999817;,
  -0.008486;-0.020364;0.999757;,
  -0.008949;-0.018904;0.999781;,
  -0.008718;-0.019108;0.999779;,
  -0.008464;-0.017464;0.999812;,
  -0.008516;-0.018794;0.999787;,
  -0.008544;-0.021612;0.999730;,
  -0.008488;-0.017965;0.999803;,
  -0.008580;-0.018102;0.999799;,
  -0.008893;-0.018548;0.999788;,
  -0.008750;-0.020302;0.999756;,
  -0.008469;-0.018738;0.999788;,
  0.007552;0.018885;-0.999793;,
  -0.009169;-0.017656;0.999802;,
  -0.009010;-0.019054;0.999778;,
  -0.008850;-0.020464;0.999751;,
  -0.008869;-0.018616;0.999787;,
  -0.008849;-0.016603;0.999823;,
  -0.008858;-0.019393;0.999773;,
  -0.008920;-0.019642;0.999767;,
  -0.009140;-0.018622;0.999785;,
  -0.009008;-0.017486;0.999806;,
  -0.008835;-0.019967;0.999762;,
  -0.009182;-0.018881;0.999780;,
  -0.009010;-0.019039;0.999778;,
  -0.008821;-0.017816;0.999802;,
  -0.008861;-0.018804;0.999784;,
  -0.008881;-0.020905;0.999742;,
  -0.008840;-0.018190;0.999795;,
  -0.008907;-0.018292;0.999793;,
  -0.009141;-0.018621;0.999785;,
  -0.009033;-0.019921;0.999761;,
  -0.008823;-0.018753;0.999785;,
  -0.002145;0.018961;-0.999818;,
  -0.009167;-0.017656;0.999802;,
  -0.009009;-0.019047;0.999778;,
  -0.008846;-0.020455;0.999752;,
  -0.008860;-0.018688;0.999786;,
  -0.008841;-0.016729;0.999821;,
  -0.008852;-0.019430;0.999772;,
  -0.008919;-0.019621;0.999768;,
  -0.009139;-0.018627;0.999785;,
  -0.009006;-0.017472;0.999807;,
  -0.008833;-0.019983;0.999761;,
  -0.009182;-0.018887;0.999780;,
  -0.009011;-0.019041;0.999778;,
  -0.008826;-0.017794;0.999803;,
  -0.008875;-0.018748;0.999785;,
  -0.008895;-0.020869;0.999743;,
  -0.008849;-0.018153;0.999796;,
  -0.008908;-0.018298;0.999793;,
  -0.009141;-0.018620;0.999785;,
  -0.009032;-0.019946;0.999760;,
  -0.008820;-0.018747;0.999785;,
  0.008099;0.018865;-0.999789;,
  -0.999908;0.009517;-0.009693;,
  -0.009877;-0.018828;0.999774;,
  0.009877;0.018827;-0.999774;,
  0.162480;-0.030157;-0.986251;,
  0.141620;-0.070683;-0.987394;,
  0.107223;-0.106465;-0.988518;,
  0.060898;-0.132713;-0.989282;,
  0.006575;-0.145878;-0.989281;,
  -0.051659;-0.142848;-0.988396;,
  -0.107422;-0.123004;-0.986575;,
  -0.153537;-0.086701;-0.984332;,
  -0.184727;-0.036806;-0.982100;,
  -0.195329;0.020373;-0.980526;,
  -0.183622;0.077403;-0.979945;,
  -0.151480;0.126785;-0.980296;,
  -0.104686;0.162276;-0.981176;,
  -0.048514;0.181145;-0.982259;,
  0.009846;0.183118;-0.983042;,
  0.063896;0.168959;-0.983550;,
  0.109684;0.141818;-0.983797;,
  0.143379;0.105371;-0.984042;,
  0.163416;0.064426;-0.984451;,
  0.169513;0.017049;-0.985380;,
  0.231462;-0.052098;-0.971448;,
  0.198786;-0.109379;-0.973920;,
  0.146717;-0.156825;-0.976668;,
  0.079976;-0.187716;-0.978962;,
  0.006131;-0.198512;-0.980079;,
  -0.068021;-0.187438;-0.979918;,
  -0.134526;-0.156508;-0.978472;,
  -0.186334;-0.108449;-0.976483;,
  -0.219951;-0.047177;-0.974370;,
  -0.231093;0.020566;-0.972714;,
  -0.218667;0.088114;-0.971813;,
  -0.183869;0.148828;-0.971618;,
  -0.131131;0.195994;-0.971798;,
  -0.064010;0.225732;-0.972084;,
  0.010399;0.235429;-0.971836;,
  0.084057;0.223206;-0.971140;,
  0.150204;0.190972;-0.970035;,
  0.201339;0.142444;-0.969109;,
  0.232853;0.084499;-0.968834;,
  0.242728;0.016105;-0.969961;,
  0.162479;-0.030168;-0.986251;,
  0.141627;-0.070689;-0.987393;,
  0.107213;-0.106474;-0.988518;,
  0.060900;-0.132727;-0.989280;,
  0.006606;-0.145875;-0.989281;,
  -0.051665;-0.142841;-0.988396;,
  -0.107447;-0.122994;-0.986574;,
  -0.153532;-0.086720;-0.984331;,
  -0.184718;-0.036805;-0.982102;,
  -0.195338;0.020377;-0.980524;,
  -0.183626;0.077379;-0.979946;,
  -0.151471;0.126784;-0.980297;,
  -0.104668;0.162284;-0.981177;,
  -0.048514;0.181150;-0.982258;,
  0.009834;0.183120;-0.983041;,
  0.063896;0.168959;-0.983550;,
  0.109683;0.141821;-0.983797;,
  0.143388;0.105357;-0.984043;,
  0.163429;0.064422;-0.984450;,
  0.169518;0.017064;-0.985379;,
  0.178033;-0.034887;-0.983406;,
  0.153184;-0.078283;-0.985092;,
  0.113633;-0.114203;-0.986937;,
  0.063027;-0.137550;-0.988488;,
  0.007081;-0.145718;-0.989301;,
  -0.049115;-0.137370;-0.989301;,
  -0.099568;-0.114020;-0.988476;,
  -0.138947;-0.077630;-0.987252;,
  -0.164547;-0.031170;-0.985877;,
  -0.173031;0.020248;-0.984708;,
  -0.163560;0.071521;-0.983937;,
  -0.137064;0.117539;-0.983564;,
  -0.096984;0.153223;-0.983421;,
  -0.046063;0.175657;-0.983373;,
  0.010329;0.182956;-0.983067;,
  0.066123;0.173714;-0.982574;,
  0.116265;0.149367;-0.981923;,
  0.155101;0.112651;-0.981455;,
  0.179075;0.068753;-0.981430;,
  0.186572;0.016852;-0.982297;;
  158;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;87,87,87,87;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  3;7,6,8;,
  3;6,5,8;,
  3;8,5,9;,
  3;5,4,9;,
  3;9,4,10;,
  3;4,3,10;,
  3;10,3,11;,
  3;3,22,11;,
  3;11,22,12;,
  3;22,21,12;,
  3;12,21,13;,
  3;21,20,13;,
  3;13,20,14;,
  3;20,19,14;,
  3;14,19,15;,
  3;19,18,15;,
  3;15,18,16;,
  3;18,17,16;,
  3;90,91,23;,
  3;91,92,23;,
  3;92,93,23;,
  3;93,94,23;,
  3;94,95,23;,
  3;95,96,23;,
  3;96,97,23;,
  3;97,98,23;,
  3;98,99,23;,
  3;99,100,23;,
  3;100,101,23;,
  3;101,102,23;,
  3;102,103,23;,
  3;103,104,23;,
  3;104,105,23;,
  3;105,106,23;,
  3;106,107,23;,
  3;107,108,23;,
  3;108,109,23;,
  3;109,90,23;,
  3;28,27,29;,
  3;27,26,29;,
  3;29,26,30;,
  3;26,25,30;,
  3;30,25,31;,
  3;25,24,31;,
  3;31,24,32;,
  3;24,43,32;,
  3;32,43,33;,
  3;43,42,33;,
  3;33,42,34;,
  3;42,41,34;,
  3;34,41,35;,
  3;41,40,35;,
  3;35,40,36;,
  3;40,39,36;,
  3;36,39,37;,
  3;39,38,37;,
  3;110,111,44;,
  3;111,112,44;,
  3;112,113,44;,
  3;113,114,44;,
  3;114,115,44;,
  3;115,116,44;,
  3;116,117,44;,
  3;117,118,44;,
  3;118,119,44;,
  3;119,120,44;,
  3;120,121,44;,
  3;121,122,44;,
  3;122,123,44;,
  3;123,124,44;,
  3;124,125,44;,
  3;125,126,44;,
  3;126,127,44;,
  3;127,128,44;,
  3;128,129,44;,
  3;129,110,44;,
  3;49,48,50;,
  3;48,47,50;,
  3;50,47,51;,
  3;47,46,51;,
  3;51,46,52;,
  3;46,45,52;,
  3;52,45,53;,
  3;45,64,53;,
  3;53,64,54;,
  3;64,63,54;,
  3;54,63,55;,
  3;63,62,55;,
  3;55,62,56;,
  3;62,61,56;,
  3;56,61,57;,
  3;61,60,57;,
  3;57,60,58;,
  3;60,59,58;,
  3;130,131,65;,
  3;131,132,65;,
  3;132,133,65;,
  3;133,134,65;,
  3;134,135,65;,
  3;135,136,65;,
  3;136,137,65;,
  3;137,138,65;,
  3;138,139,65;,
  3;139,140,65;,
  3;140,141,65;,
  3;141,142,65;,
  3;142,143,65;,
  3;143,144,65;,
  3;144,145,65;,
  3;145,146,65;,
  3;146,147,65;,
  3;147,148,65;,
  3;148,149,65;,
  3;149,130,65;,
  3;70,69,71;,
  3;69,68,71;,
  3;71,68,72;,
  3;68,67,72;,
  3;72,67,73;,
  3;67,66,73;,
  3;73,66,74;,
  3;66,85,74;,
  3;74,85,75;,
  3;85,84,75;,
  3;75,84,76;,
  3;84,83,76;,
  3;76,83,77;,
  3;83,82,77;,
  3;77,82,78;,
  3;82,81,78;,
  3;78,81,79;,
  3;81,80,79;,
  3;150,151,86;,
  3;151,152,86;,
  3;152,153,86;,
  3;153,154,86;,
  3;154,155,86;,
  3;155,156,86;,
  3;156,157,86;,
  3;157,158,86;,
  3;158,159,86;,
  3;159,160,86;,
  3;160,161,86;,
  3;161,162,86;,
  3;162,163,86;,
  3;163,164,86;,
  3;164,165,86;,
  3;165,166,86;,
  3;166,167,86;,
  3;167,168,86;,
  3;168,169,86;,
  3;169,150,86;;
 }
 MeshTextureCoords {
  182;
  0.041370;0.866262;,
  0.042840;0.928366;,
  0.192068;0.927755;,
  0.190598;0.865650;,
  0.341296;0.927143;,
  0.339826;0.865038;,
  0.490524;0.926532;,
  0.489055;0.864427;,
  0.639753;0.925920;,
  0.638283;0.863815;,
  0.044309;0.990471;,
  0.193537;0.989860;,
  0.039900;0.804157;,
  0.189129;0.803545;,
  0.884270;0.803766;,
  0.870607;0.805930;,
  0.897932;0.805930;,
  0.858282;0.812210;,
  0.910257;0.812210;,
  0.848501;0.821991;,
  0.920039;0.821991;,
  0.842221;0.834317;,
  0.926319;0.834317;,
  0.840057;0.847979;,
  0.928483;0.847979;,
  0.842221;0.861642;,
  0.926319;0.861642;,
  0.848501;0.873967;,
  0.920039;0.873967;,
  0.858282;0.883748;,
  0.910257;0.883748;,
  0.870607;0.890028;,
  0.897932;0.890028;,
  0.884270;0.892192;,
  0.928483;0.892192;,
  0.924061;0.892192;,
  0.884270;0.980618;,
  0.919640;0.892192;,
  0.915219;0.892192;,
  0.910797;0.892192;,
  0.906376;0.892192;,
  0.901955;0.892192;,
  0.897534;0.892192;,
  0.893112;0.892192;,
  0.888691;0.892192;,
  0.884270;0.892192;,
  0.879848;0.892192;,
  0.875427;0.892192;,
  0.871006;0.892192;,
  0.866584;0.892192;,
  0.862163;0.892192;,
  0.857742;0.892192;,
  0.853321;0.892192;,
  0.848899;0.892192;,
  0.844478;0.892192;,
  0.840057;0.892192;,
  0.884270;0.301239;,
  0.870607;0.303403;,
  0.897932;0.303403;,
  0.858282;0.309683;,
  0.910257;0.309683;,
  0.848501;0.319464;,
  0.920039;0.319465;,
  0.842221;0.331790;,
  0.926319;0.331790;,
  0.840057;0.345452;,
  0.928483;0.345452;,
  0.842221;0.359115;,
  0.926319;0.359115;,
  0.848501;0.371440;,
  0.920039;0.371440;,
  0.858282;0.381221;,
  0.910257;0.381221;,
  0.870607;0.387501;,
  0.897932;0.387501;,
  0.884270;0.389665;,
  0.928483;0.389665;,
  0.924061;0.389665;,
  0.884270;0.478091;,
  0.919640;0.389665;,
  0.915219;0.389665;,
  0.910797;0.389665;,
  0.906376;0.389665;,
  0.901955;0.389665;,
  0.897534;0.389665;,
  0.893112;0.389665;,
  0.888691;0.389665;,
  0.884270;0.389665;,
  0.879848;0.389665;,
  0.875427;0.389665;,
  0.871006;0.389665;,
  0.866584;0.389665;,
  0.862163;0.389665;,
  0.857742;0.389665;,
  0.853321;0.389665;,
  0.848899;0.389665;,
  0.844478;0.389665;,
  0.840057;0.389665;,
  0.884270;0.803766;,
  0.870607;0.805930;,
  0.897932;0.805930;,
  0.858282;0.812210;,
  0.910257;0.812210;,
  0.848501;0.821991;,
  0.920039;0.821991;,
  0.842221;0.834317;,
  0.926319;0.834317;,
  0.840057;0.847979;,
  0.928483;0.847979;,
  0.842221;0.861642;,
  0.926319;0.861642;,
  0.848501;0.873967;,
  0.920039;0.873967;,
  0.858282;0.883748;,
  0.910257;0.883748;,
  0.870607;0.890028;,
  0.897932;0.890028;,
  0.884270;0.892192;,
  0.928483;0.892192;,
  0.924061;0.892192;,
  0.884270;0.980618;,
  0.919640;0.892192;,
  0.915219;0.892192;,
  0.910797;0.892192;,
  0.906376;0.892192;,
  0.901955;0.892192;,
  0.897534;0.892192;,
  0.893112;0.892192;,
  0.888691;0.892192;,
  0.884270;0.892192;,
  0.879848;0.892192;,
  0.875427;0.892192;,
  0.871006;0.892192;,
  0.866584;0.892192;,
  0.862163;0.892192;,
  0.857742;0.892192;,
  0.853321;0.892192;,
  0.848899;0.892192;,
  0.844478;0.892192;,
  0.840057;0.892192;,
  0.884270;0.301239;,
  0.870607;0.303403;,
  0.897932;0.303403;,
  0.858282;0.309683;,
  0.910257;0.309683;,
  0.848501;0.319464;,
  0.920039;0.319465;,
  0.842221;0.331790;,
  0.926319;0.331790;,
  0.840057;0.345452;,
  0.928483;0.345452;,
  0.842221;0.359115;,
  0.926319;0.359115;,
  0.848501;0.371440;,
  0.920039;0.371440;,
  0.858282;0.381221;,
  0.910257;0.381221;,
  0.870607;0.387501;,
  0.897932;0.387501;,
  0.884270;0.389665;,
  0.928483;0.389665;,
  0.924061;0.389665;,
  0.884270;0.478091;,
  0.919640;0.389665;,
  0.915219;0.389665;,
  0.910797;0.389665;,
  0.906376;0.389665;,
  0.901955;0.389665;,
  0.897534;0.389665;,
  0.893112;0.389665;,
  0.888691;0.389665;,
  0.884270;0.389665;,
  0.879848;0.389665;,
  0.875427;0.389665;,
  0.871006;0.389665;,
  0.866584;0.389665;,
  0.862163;0.389665;,
  0.857742;0.389665;,
  0.853321;0.389665;,
  0.848899;0.389665;,
  0.844478;0.389665;,
  0.840057;0.389665;;
 }
}
