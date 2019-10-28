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
 162;
 -4.75822;18.23750;-12.58248;,
 2.16447;19.29842;-12.61065;,
 0.16656;13.80265;-14.30315;,
 -8.56185;13.82626;-11.40288;,
 -4.99376;26.50040;4.78691;,
 0.12229;25.35746;8.40511;,
 0.16656;28.22510;0.21459;,
 -8.36284;25.12178;0.16472;,
 -4.75822;18.23750;12.61449;,
 -8.56185;13.82626;11.43490;,
 0.16656;13.80265;14.41816;,
 2.16447;19.29842;12.64268;,
 0.16656;-0.25066;0.21459;,
 0.11669;2.68206;8.26296;,
 -4.99376;1.30343;4.78691;,
 -8.36284;2.68206;0.16472;,
 -12.63051;18.47007;4.78691;,
 -12.68686;20.35934;0.18374;,
 -14.51717;13.80265;0.21459;,
 -12.68686;13.81807;6.72502;,
 12.56646;18.47007;4.78691;,
 11.38687;13.82626;8.46198;,
 14.28714;13.80265;0.21459;,
 11.18785;22.02307;0.16472;,
 0.12229;25.35746;-8.37310;,
 -4.99376;26.50040;-4.75490;,
 -12.63051;18.47007;-4.75490;,
 -12.68686;13.81807;-6.69301;,
 -14.51717;13.80265;0.21459;,
 -12.68686;20.35934;0.18374;,
 -4.99376;1.30343;-4.75490;,
 0.11669;2.68206;-8.23095;,
 12.56646;18.47007;-4.75490;,
 11.18785;22.02307;0.16472;,
 14.28714;13.80265;0.21459;,
 11.38687;13.82626;-8.42997;,
 4.42879;1.30343;-4.75490;,
 6.34155;1.24708;0.18374;,
 4.42879;1.30343;4.78691;,
 2.16447;19.29842;12.64268;,
 6.34154;13.81807;12.67086;,
 4.42879;26.50040;4.78691;,
 6.34154;26.55676;0.18374;,
 4.42879;26.50040;-4.75490;,
 2.16447;19.29842;-12.61065;,
 6.34154;13.81807;-12.63883;,
 2.16447;8.33807;-12.61065;,
 -4.75822;9.39937;-12.58248;,
 2.16447;8.33807;-12.61065;,
 -12.63051;9.16680;-4.75490;,
 -12.68686;7.27677;0.18374;,
 -12.63051;9.16680;4.78691;,
 -12.68686;7.27677;0.18374;,
 -4.75822;9.39937;12.61449;,
 2.16447;8.33807;12.64268;,
 2.16447;8.33807;12.64268;,
 12.56646;9.16680;4.78691;,
 11.18785;5.69690;0.16472;,
 12.56646;9.16680;-4.75490;,
 11.18785;5.69690;0.16472;,
 -9.40506;4.52889;-4.95315;,
 -9.40506;8.99489;-9.35703;,
 -9.40506;18.68473;-9.35703;,
 -9.40506;23.27496;-4.95315;,
 -9.40506;23.27496;4.98517;,
 -9.40506;18.68473;9.38904;,
 -9.40506;8.99489;9.38904;,
 -9.40506;4.52889;4.98517;,
 8.62378;5.24613;-6.43785;,
 11.18785;5.69690;0.16472;,
 8.62378;5.24613;6.46987;,
 9.34101;8.99489;9.38904;,
 11.38687;13.82626;8.46198;,
 9.34101;18.68473;9.38904;,
 8.62378;22.55772;6.46987;,
 11.18785;22.02307;0.16472;,
 8.62378;22.55772;-6.43785;,
 9.34101;18.68473;-9.35703;,
 11.38687;13.82626;-8.42997;,
 9.34101;8.99489;-9.35703;,
 8.62378;22.55772;6.46987;,
 4.68868;23.27496;9.38904;,
 0.12229;25.35746;8.40511;,
 -6.54800;22.55772;8.67181;,
 -6.54800;22.55772;8.67181;,
 -9.40506;23.27496;4.98517;,
 -8.36284;25.12178;0.16472;,
 -9.40506;23.27496;-4.95315;,
 -8.36284;25.12178;0.16472;,
 -6.54800;22.55772;-8.63980;,
 -6.54800;22.55772;-8.63980;,
 0.12229;25.35746;-8.37310;,
 4.68868;23.27496;-9.35703;,
 8.62378;22.55772;-6.43785;,
 8.62378;22.55772;-6.43785;,
 8.62378;22.55772;6.46987;,
 8.62378;5.24613;-6.43785;,
 4.68868;4.52889;-9.35703;,
 0.11669;2.68206;-8.23095;,
 -6.54800;5.24613;-8.63980;,
 -6.54800;5.24613;-8.63980;,
 -9.40506;4.52889;-4.95315;,
 -8.36284;2.68206;0.16472;,
 -9.40506;4.52889;4.98517;,
 -8.36284;2.68206;0.16472;,
 -6.54800;5.24613;8.67181;,
 -6.54800;5.24613;8.67181;,
 0.11669;2.68206;8.26296;,
 4.68868;4.52889;9.38904;,
 8.62378;5.24613;6.46987;,
 8.62378;5.24613;6.46987;,
 8.62378;5.24613;-6.43785;,
 -12.63051;18.47007;-4.75490;,
 -9.40506;23.27496;-4.95315;,
 -12.68686;13.81807;-6.69301;,
 -8.56185;13.82626;-11.40288;,
 -12.63051;9.16680;-4.75490;,
 -9.40506;4.52889;-4.95315;,
 -6.54800;5.24613;-8.63980;,
 -6.54800;5.24613;-8.63980;,
 4.68868;4.52889;-9.35703;,
 8.62378;5.24613;-6.43785;,
 12.56646;9.16680;-4.75490;,
 11.38687;13.82626;-8.42997;,
 12.56646;18.47007;-4.75490;,
 -6.54800;5.24613;8.67181;,
 -9.40506;8.99489;9.38904;,
 -8.56185;13.82626;11.43490;,
 -9.40506;18.68473;9.38904;,
 -6.54800;22.55772;8.67181;,
 8.62378;22.55772;6.46987;,
 9.34101;18.68473;9.38904;,
 9.34101;8.99489;9.38904;,
 8.62378;5.24613;6.46987;,
 -0.43175;39.05724;-0.16192;,
 1.47825;39.05724;-0.16192;,
 -0.05905;33.97853;-3.91091;,
 -1.96906;33.97853;-3.91091;,
 0.95500;27.62830;-0.95500;,
 -0.95500;27.62830;-0.95500;,
 1.47825;39.05724;-0.16192;,
 1.47825;39.05724;1.74808;,
 -0.05905;33.97853;-2.00091;,
 -0.05905;33.97853;-3.91091;,
 0.95500;27.62830;0.95500;,
 0.95500;27.62830;-0.95500;,
 1.47825;39.05724;1.74808;,
 -0.43175;39.05724;1.74808;,
 -1.96906;33.97853;-2.00091;,
 -0.05905;33.97853;-2.00091;,
 -0.95500;27.62830;0.95500;,
 0.95500;27.62830;0.95500;,
 -0.43175;39.05724;1.74808;,
 -0.43175;39.05724;-0.16192;,
 -1.96906;33.97853;-3.91091;,
 -1.96906;33.97853;-2.00091;,
 -0.95500;27.62830;-0.95500;,
 -0.95500;27.62830;0.95500;,
 1.47825;39.05724;-0.16192;,
 -0.43175;39.05724;-0.16192;,
 -0.95500;27.62830;-0.95500;,
 0.95500;27.62830;-0.95500;;
 
 154;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,6;,
 3;4,6,7;,
 3;8,9,10;,
 3;8,10,11;,
 3;12,13,14;,
 3;12,14,15;,
 3;16,17,18;,
 3;16,18,19;,
 3;20,21,22;,
 3;20,22,23;,
 3;6,24,25;,
 3;6,25,7;,
 3;26,27,28;,
 3;26,28,29;,
 3;30,31,12;,
 3;30,12,15;,
 3;32,33,34;,
 3;32,34,35;,
 3;36,37,12;,
 3;36,12,31;,
 3;38,13,12;,
 3;38,12,37;,
 3;39,10,40;,
 3;41,42,6;,
 3;41,6,5;,
 3;43,24,6;,
 3;43,6,42;,
 3;44,45,2;,
 3;46,2,45;,
 3;47,3,2;,
 3;47,2,48;,
 3;49,50,28;,
 3;49,28,27;,
 3;51,19,18;,
 3;51,18,52;,
 3;53,54,10;,
 3;53,10,9;,
 3;55,40,10;,
 3;56,57,22;,
 3;56,22,21;,
 3;58,35,34;,
 3;58,34,59;,
 3;60,30,15;,
 3;3,47,61;,
 3;62,0,3;,
 3;7,25,63;,
 3;64,4,7;,
 3;9,8,65;,
 3;66,53,9;,
 3;15,14,67;,
 3;37,36,68;,
 3;37,68,69;,
 3;70,38,37;,
 3;70,37,69;,
 3;40,55,71;,
 3;40,71,72;,
 3;73,39,40;,
 3;73,40,72;,
 3;42,41,74;,
 3;42,74,75;,
 3;76,43,42;,
 3;76,42,75;,
 3;45,44,77;,
 3;45,77,78;,
 3;79,46,45;,
 3;79,45,78;,
 3;80,81,39;,
 3;80,39,73;,
 3;11,81,82;,
 3;83,8,11;,
 3;83,11,82;,
 3;8,84,65;,
 3;17,16,85;,
 3;17,85,86;,
 3;87,26,29;,
 3;87,29,88;,
 3;0,62,89;,
 3;1,0,90;,
 3;1,90,91;,
 3;92,1,91;,
 3;44,92,93;,
 3;44,93,77;,
 3;33,32,94;,
 3;95,20,23;,
 3;96,97,46;,
 3;96,46,79;,
 3;48,97,98;,
 3;99,47,48;,
 3;99,48,98;,
 3;47,100,61;,
 3;101,102,50;,
 3;101,50,49;,
 3;103,51,52;,
 3;103,52,104;,
 3;53,66,105;,
 3;54,53,106;,
 3;54,106,107;,
 3;108,54,107;,
 3;55,108,109;,
 3;55,109,71;,
 3;110,57,56;,
 3;111,58,59;,
 3;93,92,43;,
 3;24,43,92;,
 3;24,90,25;,
 3;25,89,63;,
 3;112,113,89;,
 3;112,89,62;,
 3;114,112,62;,
 3;114,62,115;,
 3;61,116,114;,
 3;61,114,115;,
 3;100,117,116;,
 3;100,116,61;,
 3;30,60,118;,
 3;31,30,119;,
 3;120,36,31;,
 3;36,120,121;,
 3;122,96,79;,
 3;123,122,79;,
 3;77,124,123;,
 3;124,77,93;,
 3;109,108,38;,
 3;13,38,108;,
 3;13,106,14;,
 3;14,105,67;,
 3;51,103,125;,
 3;51,125,126;,
 3;19,51,126;,
 3;19,126,127;,
 3;128,16,19;,
 3;128,19,127;,
 3;16,128,129;,
 3;16,129,85;,
 3;4,64,84;,
 3;5,4,83;,
 3;81,41,5;,
 3;41,81,80;,
 3;20,130,131;,
 3;21,20,131;,
 3;132,56,21;,
 3;133,56,132;,
 4;134,135,136,137;,
 4;137,136,138,139;,
 4;140,141,142,143;,
 4;143,142,144,145;,
 4;146,147,148,149;,
 4;149,148,150,151;,
 4;152,153,154,155;,
 4;155,154,156,157;,
 4;152,141,158,159;,
 4;160,161,144,157;;
 
 MeshMaterialList {
  1;
  154;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\game105\\Desktop\\MODEL\\UV\\suika.jpg";
   }
  }
 }
 MeshNormals {
  87;
  0.812547;0.582885;0.003576;,
  -0.566505;0.824055;0.002405;,
  0.806253;-0.591559;0.003610;,
  -0.028495;-0.801363;-0.597499;,
  -0.025163;-0.999674;0.004418;,
  -0.028075;-0.798372;0.601510;,
  -0.020366;0.793788;0.607853;,
  -0.020893;0.999772;0.004430;,
  -0.020770;0.796722;-0.603989;,
  0.825292;-0.000241;-0.564707;,
  -0.039324;-0.000423;-0.999226;,
  -0.552760;-0.000282;-0.833340;,
  -0.999982;-0.000361;0.005946;,
  -0.555149;-0.000283;0.831751;,
  -0.039074;-0.000440;0.999236;,
  0.822554;-0.000244;0.568688;,
  0.999993;-0.001161;0.003447;,
  -0.556717;-0.830699;0.002319;,
  -0.415532;-0.619943;-0.665585;,
  -0.426561;0.606441;-0.671025;,
  -0.426561;0.606441;0.671025;,
  -0.415532;-0.619943;0.665585;,
  0.357010;-0.637867;-0.682400;,
  0.524315;-0.851505;0.005713;,
  0.357009;-0.637868;0.682399;,
  0.458054;-0.000466;0.888924;,
  0.380790;0.622452;0.683777;,
  0.534391;0.845218;0.005779;,
  0.380791;0.622451;-0.683778;,
  0.454234;-0.000462;-0.890882;,
  0.613020;0.369197;0.698498;,
  0.186776;0.455457;0.870445;,
  -0.310863;0.361821;0.878891;,
  -0.665493;0.349766;0.659381;,
  -0.862161;0.506610;0.004995;,
  -0.665493;0.349766;-0.659381;,
  -0.309017;0.357675;-0.881236;,
  0.185640;0.452734;-0.872107;,
  0.613019;0.369198;-0.698499;,
  0.611761;-0.375241;-0.696379;,
  0.183370;-0.468774;-0.864075;,
  -0.309928;-0.364361;-0.878172;,
  -0.663651;-0.355642;-0.658093;,
  -0.856165;-0.516677;0.005138;,
  -0.663651;-0.355642;0.658093;,
  -0.311775;-0.368509;0.875784;,
  0.184502;-0.471482;0.862359;,
  0.611762;-0.375240;0.696378;,
  0.630243;0.620971;-0.466035;,
  0.337348;0.872178;-0.354262;,
  -0.359387;0.869711;-0.338296;,
  -0.683137;0.650625;-0.331679;,
  -0.845843;0.376015;-0.378367;,
  -0.864373;-0.000308;-0.502851;,
  -0.842240;-0.383009;-0.379389;,
  -0.676206;-0.657091;-0.333131;,
  -0.340297;-0.875352;-0.343448;,
  0.311306;-0.880011;-0.358706;,
  0.624894;-0.627691;-0.464233;,
  0.868501;-0.367246;-0.332920;,
  0.871774;0.359891;-0.332398;,
  0.623127;-0.625797;0.469138;,
  0.312230;-0.876785;0.365733;,
  -0.341861;-0.873079;0.347656;,
  -0.674512;-0.655656;0.339337;,
  -0.839469;-0.383144;0.385347;,
  -0.861829;-0.000311;0.507199;,
  -0.843104;0.376188;0.384263;,
  -0.681478;0.649240;0.337750;,
  -0.360870;0.867441;0.342518;,
  0.338161;0.868985;0.361264;,
  0.628451;0.619118;0.470894;,
  0.869549;0.360881;0.337119;,
  0.866277;-0.368190;0.337639;,
  0.000000;0.892719;-0.450613;,
  0.000000;0.593895;-0.804542;,
  0.000000;-0.422003;-0.906594;,
  0.957113;-0.289714;-0.000000;,
  0.997703;-0.067737;-0.000000;,
  0.987489;0.157690;0.000000;,
  0.000000;-0.593895;0.804542;,
  0.000000;0.422003;0.906594;,
  -0.957113;0.289714;0.000000;,
  -0.997703;0.067737;0.000000;,
  -0.987489;-0.157690;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  154;
  3;36,37,10;,
  3;36,10,11;,
  3;69,6,7;,
  3;69,7,1;,
  3;32,13,14;,
  3;32,14,31;,
  3;4,5,63;,
  3;4,63,17;,
  3;67,34,12;,
  3;67,12,66;,
  3;72,15,16;,
  3;72,16,0;,
  3;7,8,50;,
  3;7,50,1;,
  3;52,53,12;,
  3;52,12,34;,
  3;56,3,4;,
  3;56,4,17;,
  3;60,0,16;,
  3;60,16,9;,
  3;57,23,4;,
  3;57,4,3;,
  3;62,5,4;,
  3;62,4,23;,
  3;31,14,25;,
  3;70,27,7;,
  3;70,7,6;,
  3;49,8,7;,
  3;49,7,27;,
  3;37,29,10;,
  3;40,10,29;,
  3;41,11,10;,
  3;41,10,40;,
  3;54,43,12;,
  3;54,12,53;,
  3;65,66,12;,
  3;65,12,43;,
  3;45,46,14;,
  3;45,14,13;,
  3;46,25,14;,
  3;73,2,16;,
  3;73,16,15;,
  3;59,9,16;,
  3;59,16,2;,
  3;55,56,17;,
  3;11,41,42;,
  3;35,36,11;,
  3;1,50,51;,
  3;68,69,1;,
  3;13,32,33;,
  3;44,45,13;,
  3;17,63,64;,
  3;23,57,58;,
  3;23,58,2;,
  3;61,62,23;,
  3;61,23,2;,
  3;25,46,47;,
  3;25,47,15;,
  3;30,31,25;,
  3;30,25,15;,
  3;27,70,71;,
  3;27,71,0;,
  3;48,49,27;,
  3;48,27,0;,
  3;29,37,38;,
  3;29,38,9;,
  3;39,40,29;,
  3;39,29,9;,
  3;71,26,31;,
  3;71,31,30;,
  3;31,26,6;,
  3;20,32,31;,
  3;20,31,6;,
  3;32,20,33;,
  3;34,67,68;,
  3;34,68,1;,
  3;51,52,34;,
  3;51,34,1;,
  3;36,35,19;,
  3;37,36,19;,
  3;37,19,8;,
  3;28,37,8;,
  3;37,28,48;,
  3;37,48,38;,
  3;0,60,48;,
  3;71,72,0;,
  3;58,22,40;,
  3;58,40,39;,
  3;40,22,3;,
  3;18,41,40;,
  3;18,40,3;,
  3;41,18,42;,
  3;55,17,43;,
  3;55,43,54;,
  3;64,65,43;,
  3;64,43,17;,
  3;45,44,21;,
  3;46,45,21;,
  3;46,21,5;,
  3;24,46,5;,
  3;46,24,61;,
  3;46,61,47;,
  3;61,2,73;,
  3;58,59,2;,
  3;48,28,49;,
  3;8,49,28;,
  3;8,19,50;,
  3;50,19,51;,
  3;52,51,19;,
  3;52,19,35;,
  3;53,52,35;,
  3;53,35,11;,
  3;42,54,53;,
  3;42,53,11;,
  3;18,55,54;,
  3;18,54,42;,
  3;56,55,18;,
  3;3,56,18;,
  3;22,57,3;,
  3;57,22,58;,
  3;59,58,39;,
  3;9,59,39;,
  3;38,60,9;,
  3;60,38,48;,
  3;61,24,62;,
  3;5,62,24;,
  3;5,21,63;,
  3;63,21,64;,
  3;65,64,21;,
  3;65,21,44;,
  3;66,65,44;,
  3;66,44,13;,
  3;33,67,66;,
  3;33,66,13;,
  3;67,33,20;,
  3;67,20,68;,
  3;69,68,20;,
  3;6,69,20;,
  3;26,70,6;,
  3;70,26,71;,
  3;72,71,30;,
  3;15,72,30;,
  3;47,73,15;,
  3;61,73,47;,
  4;74,74,75,75;,
  4;76,76,76,76;,
  4;77,77,78,78;,
  4;78,78,79,79;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;82,82,83,83;,
  4;83,83,84,84;,
  4;85,85,74,74;,
  4;86,86,86,86;;
 }
 MeshTextureCoords {
  162;
  0.663070;-0.247140;,
  0.496020;-0.247140;,
  0.496020;-0.402260;,
  0.663070;-0.402260;,
  0.663070;0.359000;,
  0.496020;0.359000;,
  0.496020;0.203890;,
  0.663070;0.203890;,
  0.663070;0.646960;,
  0.663070;0.802080;,
  0.496020;0.802080;,
  0.496020;0.646960;,
  0.496020;1.396290;,
  0.496020;1.241180;,
  0.663070;1.241180;,
  0.663070;1.396290;,
  1.259280;-0.247140;,
  1.104160;-0.247140;,
  1.104160;-0.402260;,
  1.259280;-0.402260;,
  -0.259280;-0.247140;,
  -0.259280;-0.402260;,
  -0.104160;-0.402260;,
  -0.104160;-0.247140;,
  0.496020;0.040810;,
  0.663070;0.040810;,
  0.515520;-0.247140;,
  0.515520;-0.402260;,
  0.678590;-0.402260;,
  0.678590;-0.247140;,
  0.663070;1.559370;,
  0.496020;1.559370;,
  -0.085350;-0.247140;,
  -0.248420;-0.247140;,
  -0.248420;-0.402260;,
  -0.085350;-0.402260;,
  0.348860;1.559370;,
  0.348860;1.396290;,
  0.348860;1.241180;,
  0.348860;0.646960;,
  0.348860;0.802080;,
  0.348860;0.359000;,
  0.348860;0.203890;,
  0.348860;0.040810;,
  0.348860;-0.247140;,
  0.348860;-0.402260;,
  0.348860;-0.557380;,
  0.663070;-0.557380;,
  0.496020;-0.557380;,
  0.515520;-0.557380;,
  0.678590;-0.557380;,
  1.259280;-0.557380;,
  1.104160;-0.557380;,
  0.663070;0.957200;,
  0.496020;0.957200;,
  0.348860;0.957200;,
  -0.259280;-0.557380;,
  -0.104160;-0.557380;,
  -0.085350;-0.557380;,
  -0.248420;-0.557380;,
  0.800090;1.559370;,
  0.800090;-0.557380;,
  0.800090;-0.247140;,
  0.800090;0.040810;,
  0.800090;0.359000;,
  0.800090;0.646960;,
  0.800090;0.957200;,
  0.800090;1.241180;,
  0.199910;1.559370;,
  0.199910;1.396290;,
  0.199910;1.241180;,
  0.199910;0.957200;,
  0.199910;0.802080;,
  0.199910;0.646960;,
  0.199910;0.359000;,
  0.199910;0.203890;,
  0.199910;0.040810;,
  0.199910;-0.247140;,
  0.199910;-0.402260;,
  0.199910;-0.557380;,
  0.199910;0.500000;,
  0.348860;0.500000;,
  0.496020;0.500000;,
  0.663070;0.500000;,
  0.800090;0.500000;,
  1.259280;-0.100180;,
  1.104160;-0.100180;,
  0.515520;-0.100180;,
  0.678590;-0.100180;,
  0.800090;-0.100180;,
  0.663070;-0.100180;,
  0.496020;-0.100180;,
  0.348860;-0.100180;,
  0.199910;-0.100180;,
  -0.085350;-0.100180;,
  -0.259280;-0.100180;,
  0.199910;-0.700360;,
  0.348860;-0.700360;,
  0.496020;-0.700360;,
  0.663070;-0.700360;,
  0.800090;-0.700360;,
  0.515520;-0.700360;,
  0.678590;-0.700360;,
  1.259280;-0.700360;,
  1.104160;-0.700360;,
  0.800090;1.100180;,
  0.663070;1.100180;,
  0.496020;1.100180;,
  0.348860;1.100180;,
  0.199910;1.100180;,
  -0.259280;-0.700360;,
  -0.085350;-0.700360;,
  0.941090;-0.247140;,
  0.941090;-0.100180;,
  0.941090;-0.402260;,
  0.800090;-0.402260;,
  0.941090;-0.557380;,
  0.941090;-0.700360;,
  0.800090;1.700360;,
  0.663070;1.700360;,
  0.348860;1.700360;,
  0.199910;1.700360;,
  0.058910;-0.557380;,
  0.058910;-0.402260;,
  0.058910;-0.247140;,
  1.400270;-0.700360;,
  1.400270;-0.557380;,
  1.400270;-0.402260;,
  1.400270;-0.247140;,
  1.400270;-0.100180;,
  -0.400270;-0.100180;,
  -0.400270;-0.247140;,
  -0.400270;-0.557380;,
  -0.400270;-0.700360;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
