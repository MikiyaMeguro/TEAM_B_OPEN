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
 143;
 7.08431;20.56541;-0.94026;,
 7.08431;19.93710;-0.94026;,
 3.73180;22.78031;-1.43328;,
 3.73180;23.84027;-1.43328;,
 7.08431;20.56541;0.94026;,
 3.73180;23.84027;1.43328;,
 7.08431;19.93710;0.94026;,
 7.08431;20.56541;0.94026;,
 3.73180;23.84027;1.43328;,
 3.73180;22.78031;1.43328;,
 7.08431;19.93710;-0.94026;,
 7.08431;19.93710;0.94026;,
 3.73180;22.78031;1.43328;,
 3.73180;22.78031;-1.43328;,
 -9.03071;7.41507;-1.56976;,
 -9.03071;7.41507;1.56976;,
 -9.03071;8.64379;1.56976;,
 -9.03071;8.64379;-1.56976;,
 8.95630;7.41507;1.56976;,
 8.95630;7.41507;-1.56976;,
 8.95630;8.64379;-1.56976;,
 8.95630;8.64379;1.56976;,
 8.95630;7.41507;1.56976;,
 8.95630;7.41507;-1.56976;,
 8.95630;8.64379;1.56976;,
 8.95630;7.41507;1.56976;,
 8.95630;8.64379;1.56976;,
 3.73180;23.84027;-1.43328;,
 3.73180;22.78031;-1.43328;,
 -3.68483;22.78031;-1.43328;,
 -3.68483;23.84027;-1.43328;,
 3.73180;23.84027;1.43328;,
 -3.68483;23.84027;1.43328;,
 3.73180;22.78031;1.43328;,
 -3.68483;22.78031;1.43328;,
 3.73180;22.78031;-1.43328;,
 -3.68483;22.78031;-1.43328;,
 -3.68483;23.84027;-1.43328;,
 -3.68483;22.78031;-1.43328;,
 -7.19640;19.93710;-0.94026;,
 -7.19640;20.56541;-0.94026;,
 -3.68483;23.84027;1.43328;,
 -7.19640;20.56541;0.94026;,
 -3.68483;22.78031;1.43328;,
 -3.68483;23.84027;1.43328;,
 -7.19640;20.56541;0.94026;,
 -7.19640;19.93710;0.94026;,
 -3.68483;22.78031;-1.43328;,
 -3.68483;22.78031;1.43328;,
 -7.19640;19.93710;0.94026;,
 -7.19640;19.93710;-0.94026;,
 -9.03071;8.64379;1.56976;,
 -9.03071;8.64379;1.56976;,
 -9.03071;7.41507;1.56976;,
 -9.03071;7.41507;1.56976;,
 -9.03071;7.41507;-1.56976;,
 0.04122;16.38467;-3.18799;,
 0.11028;12.43235;-8.52980;,
 -6.03274;12.43221;-6.03274;,
 -2.25472;16.37715;-2.25472;,
 0.04122;16.38467;3.18799;,
 0.04122;17.12909;-0.00448;,
 -3.18799;16.38467;-0.00448;,
 -2.25472;16.37715;2.25472;,
 -6.03274;12.43221;6.03274;,
 0.11028;12.43235;8.52980;,
 0.04122;16.38467;3.18799;,
 -2.25472;16.37715;2.25472;,
 -11.37889;-0.21127;-0.01600;,
 0.14711;-0.21127;-0.01600;,
 0.14711;-0.21127;11.37889;,
 -8.04776;-0.18442;8.04776;,
 -3.18799;16.38467;-0.00448;,
 -8.52980;12.43235;-0.01200;,
 -6.03274;12.43221;6.03274;,
 -2.25472;16.37715;2.25472;,
 6.03274;12.43221;6.03274;,
 8.52980;12.43235;-0.01200;,
 3.18799;16.38467;-0.00448;,
 2.25472;16.37715;2.25472;,
 8.04776;-0.18442;8.04776;,
 11.37889;-0.21127;-0.01600;,
 2.25472;16.37715;2.25472;,
 6.03274;12.43221;6.03274;,
 3.18799;16.38467;-0.00448;,
 2.25472;16.37715;2.25472;,
 6.03274;12.43221;-6.03274;,
 2.25472;16.37715;-2.25472;,
 2.25472;16.37715;-2.25472;,
 0.04122;16.38467;-3.18799;,
 -2.25472;16.37715;-2.25472;,
 0.14711;-0.21127;-11.37889;,
 -8.04776;-0.18442;-8.04776;,
 8.04776;-0.18442;-8.04776;,
 8.04776;-0.18442;-8.04776;,
 0.14711;-0.21127;-11.37889;,
 -8.04776;-0.18442;-8.04776;,
 -11.37889;-0.21127;-0.01600;,
 -8.04776;-0.18442;8.04776;,
 8.04776;-0.18442;8.04776;,
 11.37889;-0.21127;-0.01600;,
 -7.53070;12.16266;0.35974;,
 -15.46095;13.93958;0.35974;,
 -16.24881;13.93829;0.94179;,
 -7.53070;11.37479;0.94179;,
 -16.91013;13.93622;1.11190;,
 -7.53070;10.09998;1.16412;,
 -17.34725;13.93414;0.94179;,
 -7.53070;8.82519;0.94179;,
 -17.90479;13.93286;0.35974;,
 -8.15064;8.03731;0.35974;,
 -17.90479;13.93286;-0.35973;,
 -8.15064;8.03731;-0.35973;,
 -17.34725;13.93414;-0.94179;,
 -7.53070;8.82519;-0.94179;,
 -16.91013;13.93622;-1.11190;,
 -7.53070;10.09998;-1.16411;,
 -16.24881;13.93829;-0.94179;,
 -7.53070;11.37479;-0.94179;,
 -15.46095;13.93958;-0.35973;,
 -7.53070;12.16266;-0.35973;,
 -15.46095;13.93958;0.35974;,
 -7.53070;12.16266;0.35974;,
 -15.46095;13.93958;0.35974;,
 -15.46095;13.93958;-0.35973;,
 -16.24881;13.93829;0.94179;,
 -16.24881;13.93829;-0.94179;,
 -16.91013;13.93622;1.11190;,
 -16.91013;13.93622;-1.11190;,
 -17.34725;13.93414;0.94179;,
 -17.34725;13.93414;-0.94179;,
 -17.90479;13.93286;0.35974;,
 -17.90479;13.93286;-0.35973;,
 -7.53070;10.09998;-1.16411;,
 -7.53070;11.37479;-0.94179;,
 -7.53070;8.82519;-0.94179;,
 -7.53070;12.16266;-0.35973;,
 -8.15064;8.03731;-0.35973;,
 -7.53070;12.16266;0.35974;,
 -8.15064;8.03731;0.35974;,
 -7.53070;11.37479;0.94179;,
 -7.53070;8.82519;0.94179;,
 -7.53070;10.09998;1.16412;;
 
 72;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,11,10,23;,
 4;24,7,6,25;,
 4;20,0,4,26;,
 4;19,1,0,20;,
 4;27,28,29,30;,
 4;31,27,30,32;,
 4;33,31,32,34;,
 4;35,33,34,36;,
 4;37,38,39,40;,
 4;41,37,40,42;,
 4;43,44,45,46;,
 4;47,48,49,50;,
 4;40,39,14,17;,
 4;42,40,17,51;,
 4;46,45,52,53;,
 4;50,49,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,70,69,81;,
 4;82,66,65,83;,
 4;84,61,60,85;,
 4;86,57,56,87;,
 4;88,89,61,84;,
 4;62,61,89,90;,
 4;58,73,72,59;,
 4;91,69,68,92;,
 4;81,69,91,93;,
 4;78,77,86,87;,
 4;94,95,57,86;,
 4;58,57,95,96;,
 4;96,97,73,58;,
 4;74,73,97,98;,
 4;70,65,64,71;,
 4;83,65,70,80;,
 4;99,100,77,76;,
 4;86,77,100,94;,
 4;101,102,103,104;,
 4;104,103,105,106;,
 4;106,105,107,108;,
 4;108,107,109,110;,
 4;110,109,111,112;,
 4;112,111,113,114;,
 4;114,113,115,116;,
 4;116,115,117,118;,
 4;118,117,119,120;,
 4;120,119,121,122;,
 3;123,124,125;,
 3;124,126,125;,
 3;125,126,127;,
 3;126,128,127;,
 3;127,128,129;,
 3;128,130,129;,
 3;129,130,131;,
 3;130,132,131;,
 3;133,134,135;,
 3;134,136,135;,
 3;135,136,137;,
 3;136,138,137;,
 3;137,138,139;,
 3;138,140,139;,
 3;139,140,141;,
 3;140,142,141;;
 
 MeshMaterialList {
  2;
  72;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\pot2.jpg";
   }
  }
 }
 MeshNormals {
  87;
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.996969;0.077798;0.000000;,
  -0.997088;0.076259;0.000000;,
  -0.089073;0.000000;-0.996025;,
  -0.089073;0.000000;0.996025;,
  0.888636;0.458613;0.000000;,
  0.072941;0.000000;-0.997336;,
  0.377264;0.926106;0.000000;,
  0.072941;0.000000;0.997336;,
  -0.069686;0.000000;-0.997569;,
  -0.366520;0.930410;0.000000;,
  -0.069686;0.000000;0.997569;,
  0.095406;0.000000;-0.995439;,
  -0.883990;0.467505;0.000000;,
  0.095406;0.000000;0.995439;,
  0.001699;-0.999997;-0.001672;,
  -0.001638;-0.999997;-0.001672;,
  0.340493;0.877347;-0.338122;,
  -0.337064;0.877927;-0.340048;,
  0.340679;0.877423;0.337739;,
  -0.337252;0.878003;0.339665;,
  0.001699;-0.999997;0.001665;,
  -0.001638;-0.999997;0.001665;,
  0.000031;-0.999999;-0.001672;,
  0.000031;-0.999999;0.001665;,
  0.002890;0.921604;0.388121;,
  0.002891;0.921503;-0.388359;,
  0.389198;0.921154;-0.000321;,
  0.002323;0.999997;-0.000252;,
  -0.387004;0.922078;-0.000320;,
  -0.001638;-0.999999;-0.000003;,
  0.000031;-1.000000;-0.000003;,
  0.001699;-0.999999;-0.000003;,
  0.590673;0.553586;-0.587067;,
  0.005081;0.553661;-0.832727;,
  -0.586611;0.553654;-0.591062;,
  -0.832637;0.553819;-0.000558;,
  -0.587039;0.553670;0.590623;,
  0.005081;0.553661;0.832727;,
  0.591099;0.553599;0.586626;,
  0.832637;0.553819;-0.000558;,
  0.148579;0.966056;0.211331;,
  0.075354;0.935327;0.345666;,
  -0.031982;-0.014058;0.999390;,
  -0.283093;-0.517996;0.807179;,
  -0.473560;-0.801073;0.366092;,
  -0.473561;-0.801073;-0.366090;,
  -0.283093;-0.517997;-0.807179;,
  -0.031982;-0.014058;-0.999390;,
  0.075016;0.935351;-0.345675;,
  0.110236;0.981363;-0.157401;,
  0.223706;0.921677;0.316966;,
  0.175839;0.585453;0.791407;,
  0.175839;0.585454;-0.791407;,
  0.223707;0.921677;-0.316964;,
  -0.873765;-0.486348;0.000000;,
  -0.344485;-0.938792;0.000000;,
  -0.989009;-0.147852;0.000000;,
  -0.318735;0.000000;0.947844;,
  -0.318735;0.000000;-0.947844;,
  0.333774;-0.942653;-0.000000;,
  0.868901;-0.494987;-0.000000;,
  0.324598;0.000000;-0.945852;,
  0.324598;0.000000;0.945852;,
  0.989441;-0.144940;-0.000000;,
  0.691791;0.220120;-0.687729;,
  0.006252;0.220007;-0.975478;,
  -0.687306;0.220120;-0.692213;,
  -0.975495;0.220022;-0.000678;,
  -0.687801;0.220092;0.691729;,
  0.006252;0.220007;0.975478;,
  0.692284;0.220091;0.687243;,
  0.975495;0.220022;-0.000678;,
  -0.003670;0.999993;0.000000;,
  -0.004209;0.999991;0.000000;,
  -0.003933;0.999992;0.000000;,
  -0.003119;0.999995;0.000000;,
  -0.002304;0.999997;0.000000;,
  -0.002304;0.999997;0.000000;,
  0.972570;-0.039965;0.229153;,
  0.968967;-0.092501;0.229228;,
  0.962694;-0.144671;0.228671;,
  0.986738;-0.148284;-0.066025;,
  0.938551;-0.104514;-0.328935;,
  0.942885;-0.051760;-0.329071;,
  0.917736;0.000000;-0.397192;;
  72;
  4;4,4,7,7;,
  4;6,6,8,8;,
  4;5,5,9,9;,
  4;56,56,57,57;,
  4;1,1,3,3;,
  4;0,0,2,2;,
  4;58,56,56,58;,
  4;59,5,5,59;,
  4;2,6,6,2;,
  4;60,4,4,60;,
  4;7,7,10,10;,
  4;8,8,11,11;,
  4;9,9,12,12;,
  4;57,57,61,61;,
  4;10,10,13,13;,
  4;11,11,14,14;,
  4;12,12,15,15;,
  4;61,61,62,62;,
  4;13,13,63,63;,
  4;14,14,3,3;,
  4;15,15,64,64;,
  4;62,62,65,65;,
  4;27,35,36,19;,
  4;26,29,30,21;,
  4;38,39,26,21;,
  4;31,32,25,23;,
  4;30,37,38,21;,
  4;40,41,28,20;,
  4;22,25,32,33;,
  4;20,26,39,40;,
  4;28,29,26,20;,
  4;34,35,27,18;,
  4;18,27,29,28;,
  4;30,29,27,19;,
  4;36,37,30,19;,
  4;24,32,31,17;,
  4;33,32,24,16;,
  4;28,41,34,18;,
  4;66,67,35,34;,
  4;36,35,67,68;,
  4;68,69,37,36;,
  4;38,37,69,70;,
  4;71,39,38,70;,
  4;40,39,71,72;,
  4;72,73,41,40;,
  4;34,41,73,66;,
  4;52,42,43,53;,
  4;53,43,44,44;,
  4;44,44,45,45;,
  4;45,45,46,46;,
  4;46,46,47,47;,
  4;47,47,48,48;,
  4;48,48,49,49;,
  4;49,49,50,54;,
  4;54,50,51,55;,
  4;55,51,42,52;,
  3;42,51,43;,
  3;51,50,43;,
  3;43,50,74;,
  3;50,75,74;,
  3;74,75,76;,
  3;75,77,76;,
  3;76,77,78;,
  3;77,79,78;,
  3;0,0,80;,
  3;0,81,80;,
  3;80,81,82;,
  3;81,83,82;,
  3;82,83,84;,
  3;83,85,84;,
  3;84,85,86;,
  3;85,0,86;;
 }
 MeshTextureCoords {
  143;
  0.574072;0.750000;,
  0.574071;1.000000;,
  0.521435;1.000000;,
  0.521436;0.750000;,
  0.574073;0.500000;,
  0.521437;0.500000;,
  0.574075;0.255344;,
  0.574073;0.505344;,
  0.521437;0.505344;,
  0.521439;0.255344;,
  0.574076;0.254717;,
  0.574075;0.504717;,
  0.521439;0.504716;,
  0.521440;0.254716;,
  0.374997;0.999999;,
  0.124997;0.999998;,
  0.124999;0.749998;,
  0.374999;0.749999;,
  0.874997;1.000002;,
  0.624997;1.000001;,
  0.624999;0.750001;,
  0.874999;0.750002;,
  0.625001;0.504717;,
  0.625003;0.254717;,
  0.625000;0.505344;,
  0.625001;0.255344;,
  0.625000;0.500001;,
  0.846418;0.187137;,
  0.846417;0.248382;,
  0.779092;0.248382;,
  0.779094;0.187137;,
  0.846420;0.125892;,
  0.779095;0.125892;,
  0.846421;0.064648;,
  0.779097;0.064647;,
  0.846423;0.003403;,
  0.779098;0.003402;,
  0.454111;0.750000;,
  0.454110;1.000000;,
  0.412969;1.000000;,
  0.412970;0.750000;,
  0.454113;0.500000;,
  0.412971;0.500000;,
  0.454114;0.255343;,
  0.454113;0.505343;,
  0.412971;0.505343;,
  0.412973;0.255343;,
  0.454116;0.254716;,
  0.454114;0.504716;,
  0.412973;0.504716;,
  0.412974;0.254716;,
  0.375000;0.499999;,
  0.375000;0.505343;,
  0.375001;0.255343;,
  0.375001;0.504716;,
  0.375003;0.254716;,
  0.501615;0.750000;,
  0.501614;0.874149;,
  0.374998;0.874149;,
  0.374999;0.749999;,
  0.174744;-0.000699;,
  0.174744;0.124476;,
  0.048128;0.124476;,
  0.048128;-0.000700;,
  0.375001;0.634129;,
  0.501617;0.634130;,
  0.501616;0.758279;,
  0.375000;0.758278;,
  0.375002;0.383102;,
  0.501618;0.383103;,
  0.501617;0.508279;,
  0.375001;0.508278;,
  0.250174;0.749999;,
  0.250174;0.874148;,
  0.124998;0.874147;,
  0.124999;0.749998;,
  0.874998;0.874151;,
  0.749822;0.874151;,
  0.749823;0.750001;,
  0.874999;0.750002;,
  0.625001;0.508279;,
  0.625002;0.383104;,
  0.625000;0.758279;,
  0.625001;0.634130;,
  0.298128;0.124477;,
  0.298128;-0.000699;,
  0.624998;0.874150;,
  0.624999;0.750001;,
  0.298127;0.249301;,
  0.174743;0.249301;,
  0.048127;0.249300;,
  0.501619;0.258279;,
  0.375003;0.258278;,
  0.625003;0.258279;,
  0.624997;1.000001;,
  0.501613;1.000000;,
  0.374997;0.999999;,
  0.250173;0.999999;,
  0.124997;0.999998;,
  0.874997;1.000002;,
  0.749821;1.000001;,
  0.375000;0.688440;,
  0.375000;0.312500;,
  0.400000;0.312500;,
  0.400000;0.688440;,
  0.425000;0.312500;,
  0.425000;0.688440;,
  0.450000;0.312500;,
  0.450000;0.688440;,
  0.475000;0.312500;,
  0.475000;0.688440;,
  0.500000;0.312500;,
  0.500000;0.688440;,
  0.525000;0.312500;,
  0.525000;0.688440;,
  0.550000;0.312500;,
  0.550000;0.688440;,
  0.575000;0.312500;,
  0.575000;0.688440;,
  0.600000;0.312500;,
  0.600000;0.688440;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.579374;0.130460;,
  0.579374;0.182040;,
  0.549056;0.088730;,
  0.549056;0.223770;,
  0.500000;0.072791;,
  0.500000;0.239709;,
  0.450944;0.088730;,
  0.450944;0.223770;,
  0.420626;0.130460;,
  0.420626;0.182040;,
  0.500000;0.687500;,
  0.591842;0.717341;,
  0.408159;0.717341;,
  0.648603;0.795466;,
  0.351397;0.795466;,
  0.648603;0.892034;,
  0.351397;0.892034;,
  0.591841;0.970159;,
  0.408159;0.970159;,
  0.500000;1.000000;;
 }
}
