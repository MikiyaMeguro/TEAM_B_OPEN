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
 126;
 -9.51057;17.49645;3.09017;,
 -8.09018;17.49645;5.87786;,
 -6.37938;27.87847;4.58314;,
 -7.49941;27.87847;2.38496;,
 -3.09017;17.49645;9.51057;,
 -2.43670;27.87847;7.44766;,
 5.87785;17.49645;8.09017;,
 4.63489;27.87847;6.32762;,
 9.51057;17.49645;3.09017;,
 7.49940;27.87847;2.38495;,
 9.51057;17.49645;-3.09017;,
 7.49940;27.87847;-2.48845;,
 3.09017;17.49645;-9.51057;,
 2.43670;27.87847;-7.55115;,
 0.00000;17.49645;-10.00000;,
 0.00000;27.87847;-7.93709;,
 -8.09017;17.49645;-5.87785;,
 -6.37937;27.87847;-4.68663;,
 -9.51057;17.49645;-3.09017;,
 -7.49940;27.87847;-2.48845;,
 -9.51057;17.49645;3.09017;,
 -7.49941;27.87847;2.38496;,
 -8.09018;17.49645;5.87786;,
 -9.51057;17.49645;3.09017;,
 -8.09017;17.49645;-5.87785;,
 -3.09017;17.49645;9.51057;,
 5.87785;17.49645;8.09017;,
 9.51057;17.49645;3.09017;,
 9.51057;17.49645;-3.09017;,
 3.09017;17.49645;-9.51057;,
 0.00000;17.49645;-10.00000;,
 -9.51057;17.49645;-3.09017;,
 -7.49941;27.87847;2.38496;,
 -6.37938;27.87847;4.58314;,
 -6.37937;27.87847;-4.68663;,
 -2.43670;27.87847;7.44766;,
 4.63489;27.87847;6.32762;,
 7.49940;27.87847;2.38495;,
 7.49940;27.87847;-2.48845;,
 2.43670;27.87847;-7.55115;,
 0.00000;27.87847;-7.93709;,
 -7.49940;27.87847;-2.48845;,
 -1.59521;0.37370;0.51832;,
 -1.35697;0.37370;0.98589;,
 -1.35697;18.78597;0.98589;,
 -1.59521;18.78597;0.51832;,
 -0.51832;0.37370;1.59521;,
 -0.51832;18.78597;1.59521;,
 0.98589;0.37370;1.35697;,
 0.98589;18.78597;1.35697;,
 1.59521;0.37370;0.51831;,
 1.59521;18.78597;0.51831;,
 1.59521;0.37370;-0.51831;,
 1.59521;18.78597;-0.51831;,
 0.51831;0.37370;-1.59521;,
 0.51831;18.78597;-1.59521;,
 0.00000;0.37370;-1.67730;,
 0.00000;18.78597;-1.67730;,
 -1.35697;0.37370;-0.98589;,
 -1.35697;18.78597;-0.98589;,
 -1.59521;0.37370;-0.51831;,
 -1.59521;18.78597;-0.51831;,
 -1.59521;0.37370;0.51832;,
 -1.59521;18.78597;0.51832;,
 -1.35697;0.37370;0.98589;,
 -1.59521;0.37370;0.51832;,
 -1.35697;0.37370;-0.98589;,
 -0.51832;0.37370;1.59521;,
 0.98589;0.37370;1.35697;,
 1.59521;0.37370;0.51831;,
 1.59521;0.37370;-0.51831;,
 0.51831;0.37370;-1.59521;,
 0.00000;0.37370;-1.67730;,
 -1.59521;0.37370;-0.51831;,
 -1.59521;18.78597;0.51832;,
 -1.35697;18.78597;0.98589;,
 -1.35697;18.78597;-0.98589;,
 -0.51832;18.78597;1.59521;,
 0.98589;18.78597;1.35697;,
 1.59521;18.78597;0.51831;,
 1.59521;18.78597;-0.51831;,
 0.51831;18.78597;-1.59521;,
 0.00000;18.78597;-1.67730;,
 -1.59521;18.78597;-0.51831;,
 -5.74845;-0.12785;1.86778;,
 -4.88992;-0.12785;3.55273;,
 -4.88992;2.40615;3.55273;,
 -5.74845;2.40615;1.86778;,
 -1.86778;-0.12785;5.74844;,
 -1.86778;2.40615;5.74844;,
 3.55273;-0.12785;4.88992;,
 3.55273;2.40615;4.88992;,
 5.74844;-0.12785;1.86778;,
 5.74844;2.40615;1.86778;,
 5.74844;-0.12785;-1.86778;,
 5.74844;2.40615;-1.86778;,
 1.86778;-0.12785;-5.74844;,
 1.86778;2.40615;-5.74844;,
 0.00000;-0.12785;-6.04427;,
 0.00000;2.40615;-6.04427;,
 -4.88992;-0.12785;-3.55273;,
 -4.88992;2.40615;-3.55273;,
 -5.74844;-0.12785;-1.86778;,
 -5.74844;2.40615;-1.86778;,
 -5.74845;-0.12785;1.86778;,
 -5.74845;2.40615;1.86778;,
 -4.88992;-0.12785;3.55273;,
 -5.74845;-0.12785;1.86778;,
 -4.88992;-0.12785;-3.55273;,
 -1.86778;-0.12785;5.74844;,
 3.55273;-0.12785;4.88992;,
 5.74844;-0.12785;1.86778;,
 5.74844;-0.12785;-1.86778;,
 1.86778;-0.12785;-5.74844;,
 0.00000;-0.12785;-6.04427;,
 -5.74844;-0.12785;-1.86778;,
 -5.74845;2.40615;1.86778;,
 -4.88992;2.40615;3.55273;,
 -4.88992;2.40615;-3.55273;,
 -1.86778;2.40615;5.74844;,
 3.55273;2.40615;4.88992;,
 5.74844;2.40615;1.86778;,
 5.74844;2.40615;-1.86778;,
 1.86778;2.40615;-5.74844;,
 0.00000;2.40615;-6.04427;,
 -5.74844;2.40615;-1.86778;;
 
 78;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 3;22,23,24;,
 3;25,22,24;,
 3;26,25,24;,
 3;27,26,24;,
 3;28,27,24;,
 3;29,28,24;,
 3;30,29,24;,
 3;23,31,24;,
 3;32,33,34;,
 3;33,35,34;,
 3;35,36,34;,
 3;36,37,34;,
 3;37,38,34;,
 3;38,39,34;,
 3;39,40,34;,
 3;41,32,34;,
 4;42,43,44,45;,
 4;43,46,47,44;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 3;64,65,66;,
 3;67,64,66;,
 3;68,67,66;,
 3;69,68,66;,
 3;70,69,66;,
 3;71,70,66;,
 3;72,71,66;,
 3;65,73,66;,
 3;74,75,76;,
 3;75,77,76;,
 3;77,78,76;,
 3;78,79,76;,
 3;79,80,76;,
 3;80,81,76;,
 3;81,82,76;,
 3;83,74,76;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 3;106,107,108;,
 3;109,106,108;,
 3;110,109,108;,
 3;111,110,108;,
 3;112,111,108;,
 3;113,112,108;,
 3;114,113,108;,
 3;107,115,108;,
 3;116,117,118;,
 3;117,119,118;,
 3;119,120,118;,
 3;120,121,118;,
 3;121,122,118;,
 3;122,123,118;,
 3;123,124,118;,
 3;125,116,118;;
 
 MeshMaterialList {
  1;
  78;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.793726;0.793726;0.793726;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Lamp.jpg";
   }
  }
 }
 MeshNormals {
  32;
  -0.952758;0.200087;0.228511;,
  -0.744641;0.202039;0.636153;,
  -0.228143;0.203545;0.952113;,
  0.511294;0.202986;0.835090;,
  0.931667;0.201036;0.302625;,
  0.905520;0.197189;-0.375700;,
  0.445923;0.193021;-0.874011;,
  -0.154052;0.192564;-0.969117;,
  -0.693242;0.193880;-0.694137;,
  -0.953165;0.197900;-0.228717;,
  -0.972370;0.000000;0.233446;,
  -0.760407;0.000000;0.649447;,
  -0.233448;0.000000;0.972369;,
  0.522498;0.000000;0.852640;,
  0.951057;0.000000;0.309016;,
  0.923880;0.000000;-0.382683;,
  0.453989;0.000000;-0.891007;,
  -0.156436;0.000000;-0.987688;,
  -0.707109;0.000000;-0.707105;,
  -0.972371;0.000000;-0.233442;,
  -0.972370;0.000000;0.233445;,
  -0.760405;0.000000;0.649449;,
  -0.233445;0.000000;0.972370;,
  0.522499;0.000000;0.852640;,
  0.951057;0.000000;0.309017;,
  0.453991;0.000000;-0.891006;,
  -0.156434;0.000000;-0.987688;,
  -0.707108;0.000000;-0.707106;,
  -0.972370;0.000000;-0.233446;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;;
  78;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,0,0,9;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,30,29;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,10,10,19;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,15,15,24;,
  4;15,25,25,15;,
  4;25,26,26,25;,
  4;26,27,27,26;,
  4;27,28,28,27;,
  4;28,20,20,28;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;29,29,29;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;;
 }
 MeshTextureCoords {
  126;
  0.028453;0.983896;,
  0.076796;0.983896;,
  0.076796;0.503812;,
  0.028453;0.503812;,
  0.173483;0.983896;,
  0.173483;0.503812;,
  0.318513;0.983896;,
  0.318513;0.503812;,
  0.415200;0.983896;,
  0.415200;0.503812;,
  0.511886;0.983896;,
  0.511886;0.503812;,
  0.656916;0.983896;,
  0.656916;0.503812;,
  0.705259;0.983896;,
  0.705259;0.503812;,
  0.850289;0.983896;,
  0.850289;0.503812;,
  0.898633;0.983896;,
  0.898633;0.503812;,
  0.995320;0.983896;,
  0.995320;0.503812;,
  0.850732;0.847287;,
  0.918204;0.790785;,
  0.850732;0.609016;,
  0.613219;0.920917;,
  0.187216;0.892128;,
  0.014652;0.790785;,
  0.014652;0.665518;,
  0.319637;0.535386;,
  0.466428;0.525466;,
  0.918204;0.665518;,
  0.485332;0.513855;,
  0.338968;0.524862;,
  0.872981;0.594543;,
  0.104490;0.600243;,
  0.044432;0.782485;,
  0.221097;0.882532;,
  0.501844;0.919166;,
  0.882687;0.832778;,
  0.947847;0.775784;,
  0.766080;0.550488;,
  0.420022;0.325655;,
  0.419963;0.331026;,
  0.581502;0.332800;,
  0.581561;0.327429;,
  0.419845;0.341768;,
  0.581384;0.343542;,
  0.419669;0.357882;,
  0.581207;0.359656;,
  0.419551;0.368624;,
  0.581089;0.370398;,
  0.419433;0.379366;,
  0.580971;0.381140;,
  0.419256;0.395480;,
  0.580794;0.397254;,
  0.419197;0.400851;,
  0.580735;0.402625;,
  0.419020;0.416964;,
  0.580558;0.418738;,
  0.418961;0.422336;,
  0.580499;0.424110;,
  0.418843;0.433078;,
  0.580381;0.434852;,
  0.312233;0.432513;,
  0.330845;0.442255;,
  0.391160;0.433380;,
  0.288212;0.398675;,
  0.298409;0.338569;,
  0.332247;0.314548;,
  0.373742;0.315003;,
  0.416374;0.358583;,
  0.419433;0.379366;,
  0.372339;0.442710;,
  0.667753;0.445955;,
  0.686574;0.436624;,
  0.607647;0.435757;,
  0.711333;0.403322;,
  0.702457;0.343006;,
  0.669155;0.318248;,
  0.627661;0.317792;,
  0.584081;0.360425;,
  0.580567;0.381136;,
  0.626258;0.445499;,
  0.320483;0.079205;,
  0.320614;0.083673;,
  0.677299;0.082193;,
  0.677168;0.077726;,
  0.320875;0.092608;,
  0.677560;0.091129;,
  0.321267;0.106011;,
  0.677952;0.104531;,
  0.321528;0.114946;,
  0.678213;0.113467;,
  0.321789;0.123881;,
  0.678474;0.122402;,
  0.322181;0.137284;,
  0.678866;0.135805;,
  0.322311;0.141752;,
  0.678996;0.140272;,
  0.322703;0.155154;,
  0.679388;0.153675;,
  0.322834;0.159622;,
  0.679519;0.158143;,
  0.323095;0.168557;,
  0.679780;0.167078;,
  0.087725;0.170037;,
  0.129283;0.177798;,
  0.262000;0.169314;,
  0.033055;0.142338;,
  0.052648;0.092169;,
  0.126179;0.071574;,
  0.217800;0.071194;,
  0.314029;0.106654;,
  0.321789;0.123881;,
  0.220905;0.177418;,
  0.873193;0.174712;,
  0.914287;0.166609;,
  0.740012;0.167332;,
  0.967325;0.138463;,
  0.944804;0.088468;,
  0.870088;0.068489;,
  0.778466;0.068869;,
  0.684333;0.105118;,
  0.677582;0.122406;,
  0.781571;0.175092;;
 }
}
