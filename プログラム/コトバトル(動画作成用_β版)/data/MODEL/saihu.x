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
 189;
 -18.22802;15.00000;1.60681;,
 18.31844;15.00000;1.60681;,
 18.31844;15.00000;-1.58411;,
 -18.22802;15.00000;-1.58411;,
 20.00000;0.00000;-1.58411;,
 20.00000;0.00000;1.69512;,
 -20.00000;0.01847;1.69637;,
 -20.00000;0.01847;-1.58314;,
 -20.00000;11.49744;-1.58411;,
 -20.00000;11.49744;1.60681;,
 -20.00000;13.08981;1.60681;,
 -20.00000;13.08981;-1.58411;,
 20.00000;11.49744;1.60681;,
 20.00000;11.49744;-1.58411;,
 20.00000;13.08981;-1.58411;,
 20.00000;13.08981;1.60681;,
 -20.00000;0.01847;-1.59119;,
 -20.00000;-0.00284;1.69637;,
 -20.00000;11.49744;1.60681;,
 -20.00000;11.49744;-1.58411;,
 20.00000;0.00000;1.60681;,
 20.00000;0.00000;-1.58411;,
 20.00000;11.49744;-1.58411;,
 20.00000;11.49744;1.60681;,
 -20.00000;13.08981;-1.58411;,
 -20.00000;13.08981;1.60681;,
 -19.31823;14.33936;1.60681;,
 -19.31823;14.33936;-1.58411;,
 20.00000;13.08981;1.60681;,
 20.00000;13.08981;-1.58411;,
 19.31823;14.33936;-1.58411;,
 19.31823;14.33936;1.60681;,
 -20.00000;13.08981;-1.58411;,
 -19.31823;14.33936;-1.58411;,
 -20.00000;11.49744;-1.58411;,
 -20.00000;0.01847;-1.59119;,
 20.00000;0.00000;-1.58411;,
 -18.22802;15.00000;-1.58411;,
 18.31844;15.00000;-1.58411;,
 19.31823;14.33936;-1.58411;,
 20.00000;13.08981;-1.58411;,
 20.00000;11.49744;-1.58411;,
 -18.22802;15.00000;1.60681;,
 -18.22802;15.00000;-1.58411;,
 -19.31823;14.33936;-1.58411;,
 -19.31823;14.33936;1.60681;,
 20.00000;13.08981;1.60681;,
 19.31823;14.33936;1.60681;,
 20.00000;11.49744;1.60681;,
 20.00000;0.00000;1.60681;,
 -20.00000;0.00021;1.69637;,
 18.31844;15.00000;1.60681;,
 -18.22802;15.00000;1.60681;,
 -19.31823;14.33936;1.60681;,
 -20.00000;13.08981;1.60681;,
 -20.00000;11.49744;1.60681;,
 19.31823;14.33936;-1.58411;,
 18.31844;15.00000;-1.58411;,
 18.31844;15.00000;1.60681;,
 19.31823;14.33936;1.60681;,
 20.44229;2.86058;-0.66506;,
 19.68653;2.86058;-0.66506;,
 19.68653;3.40856;-0.42764;,
 20.44229;3.40856;-0.42764;,
 20.44229;3.82220;-0.03226;,
 19.68653;3.82220;-0.03226;,
 19.68653;3.40856;0.33400;,
 20.44229;3.40856;0.33400;,
 19.68653;2.86058;0.57143;,
 20.44229;2.86058;0.57143;,
 20.44229;0.91419;0.16836;,
 19.68653;0.91419;0.16836;,
 19.68653;0.91419;-0.26199;,
 20.44229;0.91419;-0.26199;,
 19.68653;2.11505;0.61601;,
 19.68653;2.86058;0.57143;,
 19.68653;1.52475;0.32635;,
 19.68653;3.40856;0.33400;,
 19.68653;3.82220;-0.03226;,
 19.68653;0.91419;0.16836;,
 19.68653;0.91419;-0.26199;,
 19.68653;3.40856;-0.42764;,
 19.68653;1.52475;-0.41998;,
 19.68653;2.11505;-0.70964;,
 19.68653;2.86058;-0.66506;,
 20.44229;2.11505;-0.70964;,
 20.44229;1.52475;-0.41998;,
 20.44229;3.82220;-0.03226;,
 20.44229;0.91419;-0.26199;,
 20.44229;0.91419;0.16836;,
 20.44229;3.40856;0.33400;,
 20.44229;1.52475;0.32635;,
 20.44229;2.11505;0.61601;,
 20.44229;2.86058;0.57143;,
 19.68653;2.11505;-0.70964;,
 19.68653;2.11505;0.61601;,
 20.44229;2.11505;0.61601;,
 19.68653;1.52475;-0.41998;,
 19.68653;1.52475;0.32635;,
 20.44229;1.52475;0.32635;,
 19.68653;0.91419;-0.26199;,
 20.89318;3.25064;-0.15992;,
 20.71128;3.24996;-0.15992;,
 20.37066;3.25132;-0.15992;,
 20.85685;3.43049;-0.15992;,
 20.37066;3.50994;-0.15992;,
 20.37066;3.50994;0.11167;,
 20.85685;3.43049;0.11167;,
 20.89318;3.25064;0.11167;,
 20.37066;3.25132;0.11167;,
 20.71128;3.24996;0.11167;,
 20.85824;1.41970;0.11167;,
 20.38224;1.34025;0.11167;,
 20.38224;1.34025;-0.15992;,
 20.85685;1.41970;-0.15992;,
 20.71128;3.24996;0.11167;,
 20.37066;3.25132;0.11167;,
 20.85983;2.42145;-0.11777;,
 20.85983;2.42145;0.06951;,
 20.85685;3.43049;0.11167;,
 20.89318;3.25064;0.11167;,
 20.89318;1.60480;-0.15992;,
 20.38224;1.60247;-0.15992;,
 20.71128;1.60713;-0.15992;,
 20.38224;1.60247;0.11167;,
 20.71128;1.60713;0.11167;,
 20.89386;1.60480;0.11167;,
 20.71128;1.60713;0.11167;,
 20.38224;1.60247;0.11167;,
 20.85685;1.41970;-0.15992;,
 20.85824;1.41970;0.11167;,
 20.89386;1.60480;0.11167;,
 20.89318;3.25064;0.11167;,
 20.37066;3.50994;0.11167;,
 20.89318;3.25064;-0.15992;,
 20.38224;1.34025;-0.15992;,
 20.89318;1.60480;-0.15992;,
 20.38224;1.34025;0.11167;,
 20.89386;1.60480;0.11167;,
 20.74464;2.42145;-0.11777;,
 20.89318;3.25064;-0.15992;,
 20.74464;2.42145;0.06951;,
 20.89318;3.25064;0.11167;,
 20.74464;2.42145;0.06951;,
 20.85983;2.42145;0.06951;,
 20.89318;1.60480;-0.15992;,
 20.89386;1.60480;0.11167;,
 20.48635;-1.13831;-0.43174;,
 20.48635;1.87287;-0.43174;,
 20.70839;1.87287;-0.43174;,
 20.70839;-1.13831;-0.43174;,
 20.70839;1.87287;-0.16042;,
 20.48635;1.87287;-0.16042;,
 20.48635;1.87287;0.15134;,
 20.70839;1.87287;0.15134;,
 20.70839;1.87287;0.42894;,
 20.48635;1.87287;0.42894;,
 20.48635;-1.13831;0.42894;,
 20.70839;-1.13831;0.42894;,
 20.70839;-1.13831;0.15134;,
 20.48635;-1.13831;0.15134;,
 20.48635;-1.13831;-0.16042;,
 20.70839;-1.13831;-0.16042;,
 20.48635;1.87287;-0.16042;,
 20.48636;1.57882;-0.22349;,
 20.48653;1.57882;0.21440;,
 20.48635;1.87287;0.15134;,
 20.70839;1.87287;0.15134;,
 20.70839;1.57882;0.21440;,
 20.70839;1.57882;-0.22349;,
 20.70839;1.87287;-0.16042;,
 20.48635;-1.13831;-0.16042;,
 20.48626;0.76214;-0.22349;,
 20.48635;-1.13831;-0.43174;,
 20.70839;-1.13831;-0.43174;,
 20.70839;-1.13831;-0.16042;,
 20.70839;0.76214;-0.22349;,
 20.48635;-1.13831;0.42894;,
 20.48635;1.87287;0.42894;,
 20.48635;-1.13831;0.15134;,
 20.48651;0.76214;0.21440;,
 20.70839;1.87287;0.42894;,
 20.70839;-1.13831;0.15134;,
 20.70839;0.76214;0.21440;,
 20.70839;-1.13831;0.42894;,
 20.48651;0.76214;0.21440;,
 20.48653;1.57882;0.21440;,
 20.48626;0.76214;-0.22349;,
 20.48636;1.57882;-0.22349;;
 
 115;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 3;32,33,34;,
 3;34,33,35;,
 3;35,33,36;,
 3;33,37,36;,
 3;37,38,36;,
 3;38,39,36;,
 3;39,40,41;,
 3;41,36,39;,
 4;42,43,44,45;,
 3;46,47,48;,
 3;48,47,49;,
 3;49,47,50;,
 3;47,51,50;,
 3;51,52,50;,
 3;52,53,50;,
 3;53,54,50;,
 3;54,55,50;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;67,66,68,69;,
 4;70,71,72,73;,
 3;74,75,76;,
 3;75,77,76;,
 3;77,78,76;,
 3;76,78,79;,
 3;79,78,80;,
 3;78,81,80;,
 3;80,81,82;,
 3;82,81,83;,
 3;81,84,83;,
 3;85,60,86;,
 3;60,63,86;,
 3;63,87,86;,
 3;86,87,88;,
 3;88,87,89;,
 3;87,90,89;,
 3;89,90,91;,
 3;91,90,92;,
 3;90,93,92;,
 4;63,62,65,64;,
 4;85,94,61,60;,
 4;69,68,95,96;,
 4;86,97,94,85;,
 4;96,95,98,99;,
 4;88,100,97,86;,
 4;99,98,71,70;,
 3;101,102,103;,
 4;104,105,106,107;,
 3;108,109,110;,
 4;111,112,113,114;,
 4;102,115,116,103;,
 3;117,101,118;,
 3;101,104,118;,
 3;104,119,118;,
 3;119,120,118;,
 3;121,122,123;,
 4;122,124,125,123;,
 3;126,127,128;,
 3;117,118,121;,
 3;121,118,129;,
 3;129,118,130;,
 3;118,131,130;,
 4;107,106,109,132;,
 4;103,116,133,105;,
 4;134,103,105,104;,
 4;129,135,122,136;,
 4;135,137,124,122;,
 4;138,128,112,111;,
 4;117,139,102,140;,
 4;139,141,115,102;,
 4;142,110,143,144;,
 4;123,125,141,139;,
 4;145,123,139,117;,
 4;144,143,127,146;,
 4;147,148,149,150;,
 4;151,152,153,154;,
 4;155,156,157,158;,
 4;159,160,161,162;,
 4;163,164,165,166;,
 4;167,168,169,170;,
 4;149,148,152,151;,
 3;171,172,147;,
 3;163,148,164;,
 3;172,164,147;,
 3;164,148,147;,
 4;162,161,173,174;,
 3;150,149,175;,
 3;149,170,169;,
 3;149,169,176;,
 3;176,175,149;,
 4;158,157,160,159;,
 3;177,178,179;,
 3;178,166,165;,
 3;165,180,178;,
 3;180,179,178;,
 4;154,153,156,155;,
 3;167,181,168;,
 3;182,183,184;,
 3;183,168,184;,
 3;168,181,184;,
 4;180,172,171,179;,
 4;176,183,182,175;,
 4;168,183,185,186;,
 4;183,176,187,185;,
 4;176,169,188,187;,
 4;169,168,186,188;;
 
 MeshMaterialList {
  1;
  115;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.570000;0.570000;0.570000;1.000000;;
   14.000000;
   0.080000;0.080000;0.080000;;
   0.090000;0.090000;0.090000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\Saifa.jpg";
   }
  }
 }
 MeshNormals {
  78;
  -0.000462;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.736322;0.676631;0.000000;,
  -0.722950;0.690901;0.000000;,
  -0.002546;0.004314;0.999988;,
  1.000000;0.000000;0.000000;,
  0.968978;0.247147;0.000000;,
  -0.986432;0.164172;0.000000;,
  -0.968978;0.247147;0.000000;,
  -0.269042;0.963128;0.000000;,
  0.287825;0.957683;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.552903;-0.833246;,
  0.000000;0.536926;0.843630;,
  0.000000;0.662932;0.748680;,
  0.000000;0.232150;-0.972680;,
  0.000000;0.232150;0.972680;,
  1.000000;0.000000;0.000000;,
  0.164857;-0.986317;-0.000419;,
  0.161274;0.986910;0.000000;,
  1.000000;0.000308;0.000000;,
  0.000213;0.000420;-1.000000;,
  -1.000000;0.000350;0.000000;,
  0.973804;0.000654;0.227389;,
  0.000032;-0.016937;0.999857;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000032;-0.016938;-0.999857;,
  0.000110;0.017218;-0.999852;,
  -0.014161;0.999900;0.000000;,
  0.000110;0.017220;0.999852;,
  0.000048;-0.025407;-0.999677;,
  0.000048;-0.025406;0.999677;,
  0.000165;0.025828;-0.999666;,
  0.000000;1.000000;0.000000;,
  -1.000000;-0.000044;-0.000320;,
  -1.000000;-0.000289;-0.000222;,
  -1.000000;0.000033;-0.000405;,
  -1.000000;0.000061;-0.000681;,
  -0.000598;0.000276;-1.000000;,
  -0.001286;0.000308;-0.999999;,
  -0.001197;0.000551;-0.999999;,
  0.000035;0.000097;-1.000000;,
  0.000927;0.000582;0.999999;,
  0.001119;0.000053;0.999999;,
  0.000734;0.004095;0.999991;,
  -0.001948;0.006200;0.999979;,
  -0.008217;0.006635;0.999944;,
  -0.012537;0.006841;0.999898;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.690971;-0.722883;,
  0.000000;-0.196932;-0.980417;,
  0.000000;-0.196928;0.980418;,
  0.000000;-0.347300;-0.937754;,
  0.000000;-0.347304;0.937753;,
  0.000000;-0.250511;-0.968114;,
  0.000000;-0.250519;0.968112;,
  -0.004008;-0.999992;0.000000;,
  0.935141;0.059044;0.349320;,
  0.933672;0.082017;0.348611;,
  0.999996;0.002949;0.000000;,
  0.205295;0.041461;-0.977821;,
  0.210388;0.000027;-0.977618;,
  0.000165;0.025831;0.999666;,
  0.938307;-0.057482;0.340992;,
  0.937755;-0.080176;0.337916;,
  0.999985;-0.001806;-0.005085;,
  0.215114;-0.041407;-0.975711;,
  -0.999190;-0.040229;0.000000;,
  0.000213;0.000424;1.000000;,
  -0.999162;0.040929;0.000000;,
  -1.000000;-0.000147;0.000099;,
  -1.000000;-0.000443;0.000099;,
  -1.000000;-0.000009;0.000145;,
  -1.000000;0.000023;-0.000492;,
  -1.000000;-0.000010;0.000015;,
  -1.000000;-0.000115;-0.000584;,
  -1.000000;0.000055;-0.000393;;
  115;
  4;9,10,10,9;,
  4;0,0,0,0;,
  4;1,1,7,8;,
  4;5,5,6,6;,
  4;1,1,1,1;,
  4;5,5,5,5;,
  4;8,7,3,3;,
  4;6,6,2,2;,
  3;26,39,40;,
  3;40,39,41;,
  3;41,39,42;,
  3;39,26,42;,
  3;26,26,42;,
  3;26,26,42;,
  3;26,26,26;,
  3;26,42,26;,
  4;9,9,3,3;,
  3;25,43,25;,
  3;25,43,44;,
  3;44,43,4;,
  3;43,45,4;,
  3;45,46,4;,
  3;46,47,4;,
  3;47,48,4;,
  3;7,1,49;,
  4;2,10,10,2;,
  4;15,15,12,12;,
  4;14,14,13,13;,
  4;13,13,16,16;,
  4;11,11,11,11;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;17,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;12,12,50,50;,
  4;51,51,15,15;,
  4;16,16,52,52;,
  4;53,53,51,51;,
  4;52,52,54,54;,
  4;55,55,53,53;,
  4;54,54,56,56;,
  3;27,31,26;,
  4;19,19,19,19;,
  3;24,25,32;,
  4;18,18,18,18;,
  4;57,57,57,57;,
  3;20,58,23;,
  3;58,59,23;,
  3;59,60,23;,
  3;61,61,62;,
  3;28,26,33;,
  4;29,29,29,29;,
  3;30,63,25;,
  3;20,23,64;,
  3;64,23,65;,
  3;65,23,66;,
  3;62,67,67;,
  4;25,25,25,24;,
  4;1,1,1,1;,
  4;27,26,26,26;,
  4;26,26,26,28;,
  4;1,1,1,1;,
  4;30,25,25,25;,
  4;21,21,31,27;,
  4;22,22,68,68;,
  4;24,32,69,69;,
  4;70,70,22,22;,
  4;28,33,21,21;,
  4;69,69,63,30;,
  4;26,26,26,26;,
  4;34,34,34,34;,
  4;25,25,25,25;,
  4;11,11,11,11;,
  4;71,35,36,72;,
  4;5,5,5,5;,
  4;34,34,34,34;,
  3;73,37,74;,
  3;71,75,35;,
  3;37,35,74;,
  3;35,75,74;,
  4;11,11,11,11;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;11,11,11,11;,
  3;1,76,77;,
  3;76,72,36;,
  3;36,38,76;,
  3;38,77,76;,
  4;34,34,34,34;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;38,37,73,77;,
  4;5,5,5,5;,
  4;26,26,26,26;,
  4;34,34,34,34;,
  4;25,25,25,25;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  189;
  0.963988;0.264414;,
  0.963925;0.955075;,
  0.852214;0.954787;,
  0.852277;0.264125;,
  0.005557;1.000000;,
  0.005557;0.750000;,
  0.757565;0.750000;,
  0.757565;1.000000;,
  0.857849;0.690189;,
  0.960737;0.690189;,
  0.960737;0.762773;,
  0.857849;0.762773;,
  0.852422;0.644758;,
  0.961166;0.644758;,
  0.961166;0.694320;,
  0.852422;0.694320;,
  0.854921;0.368969;,
  0.963665;0.368969;,
  0.963665;0.788387;,
  0.854921;0.788387;,
  0.852422;-0.001856;,
  0.961166;-0.001856;,
  0.961166;0.352917;,
  0.852422;0.352917;,
  0.855426;0.653544;,
  0.963160;0.653544;,
  0.963160;0.716577;,
  0.855426;0.716577;,
  0.852422;0.649571;,
  0.961166;0.649571;,
  0.961166;0.697773;,
  0.852422;0.697773;,
  0.749211;0.915650;,
  0.749211;0.953112;,
  0.749211;0.884421;,
  0.749211;0.658935;,
  0.004800;0.658935;,
  0.716234;0.953112;,
  0.036094;0.953112;,
  0.004800;0.953112;,
  0.004800;0.915650;,
  0.004800;0.884421;,
  0.960349;0.570193;,
  0.861968;0.570462;,
  0.861583;0.512347;,
  0.959964;0.512079;,
  0.003051;0.741980;,
  0.003051;0.704121;,
  0.003051;0.773540;,
  0.003051;1.001414;,
  0.741850;1.001414;,
  0.034110;0.704121;,
  0.709121;0.704121;,
  0.741850;0.704121;,
  0.741850;0.741980;,
  0.741850;0.773540;,
  0.847985;0.391191;,
  0.848172;0.334855;,
  0.965724;0.336032;,
  0.965537;0.392368;,
  0.082243;0.073070;,
  0.138794;0.073070;,
  0.138794;0.084756;,
  0.082243;0.084756;,
  0.082243;0.108395;,
  0.138794;0.108395;,
  0.138794;0.131017;,
  0.082243;0.131017;,
  0.138794;0.142703;,
  0.082243;0.142703;,
  0.082243;0.177279;,
  0.138794;0.177279;,
  0.138794;0.223540;,
  0.082243;0.223540;,
  0.746587;0.121513;,
  0.746587;0.186849;,
  0.783030;0.051718;,
  0.746587;0.250000;,
  0.660776;0.250000;,
  0.783030;0.000000;,
  0.533030;0.000000;,
  0.533030;0.250000;,
  0.533030;0.051718;,
  0.533030;0.121513;,
  0.533030;0.186849;,
  0.082243;0.060980;,
  0.082243;0.048065;,
  0.053346;0.084756;,
  0.082243;0.038495;,
  0.025692;0.038495;,
  0.025692;0.084756;,
  0.025692;0.048065;,
  0.025692;0.060980;,
  0.025692;0.073070;,
  0.138794;0.060980;,
  0.138794;0.154793;,
  0.082243;0.154793;,
  0.138794;0.048065;,
  0.138794;0.167708;,
  0.082243;0.167708;,
  0.138794;0.038495;,
  0.082243;0.078669;,
  0.138794;0.078096;,
  0.138794;0.079242;,
  0.082243;0.084756;,
  0.138794;0.084756;,
  0.138794;0.131017;,
  0.082243;0.131017;,
  0.082243;0.137104;,
  0.138794;0.136531;,
  0.138794;0.137677;,
  0.082243;0.177279;,
  0.138794;0.177279;,
  0.138794;0.223540;,
  0.082243;0.223540;,
  0.195344;0.078096;,
  0.195344;0.079242;,
  0.082243;0.061548;,
  0.025692;0.061548;,
  0.025692;0.084756;,
  0.025692;0.078669;,
  0.082243;0.043881;,
  0.138794;0.043577;,
  0.138794;0.044185;,
  0.195344;0.043577;,
  0.195344;0.044185;,
  0.082243;0.171892;,
  0.138794;0.171588;,
  0.138794;0.172196;,
  0.082243;0.038495;,
  0.025692;0.038495;,
  0.025692;0.043881;,
  0.082243;0.136531;,
  0.195344;0.084756;,
  0.082243;0.079242;,
  0.138794;0.038495;,
  0.082243;0.043577;,
  0.195344;0.038495;,
  0.082243;0.172196;,
  0.138794;0.061548;,
  0.082243;0.078096;,
  0.195344;0.061548;,
  0.082243;0.137677;,
  0.138794;0.154226;,
  0.082243;0.154226;,
  0.082243;0.044185;,
  0.082243;0.171588;,
  0.138794;0.038495;,
  0.138794;0.084756;,
  0.082243;0.084756;,
  0.082243;0.038495;,
  0.082243;0.099339;,
  0.138794;0.099339;,
  0.138794;0.116096;,
  0.082243;0.116096;,
  0.082243;0.131017;,
  0.138794;0.131017;,
  0.138794;0.177279;,
  0.082243;0.177279;,
  0.082243;0.192199;,
  0.138794;0.192199;,
  0.138794;0.208957;,
  0.082243;0.208957;,
  0.156620;0.084756;,
  0.156620;0.077729;,
  0.177105;0.077729;,
  0.177105;0.084756;,
  0.043932;0.084756;,
  0.043932;0.077729;,
  0.064416;0.077729;,
  0.064416;0.084756;,
  0.156620;0.038495;,
  0.156620;0.069311;,
  0.138794;0.223540;,
  0.082243;0.223540;,
  0.064416;0.038495;,
  0.064416;0.069311;,
  0.195344;0.038495;,
  0.195344;0.084756;,
  0.177105;0.038495;,
  0.177105;0.069311;,
  0.025692;0.084756;,
  0.043932;0.038495;,
  0.043932;0.069311;,
  0.025692;0.038495;,
  0.043932;0.069311;,
  0.043932;0.077729;,
  0.064416;0.069311;,
  0.064416;0.077729;;
 }
}
