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
 254;
 -7.51673;2.14269;-0.45135;,
 -6.15973;2.16786;-0.11200;,
 -6.02419;1.87741;-1.04075;,
 -6.88402;1.87444;-1.02597;,
 -9.28283;-0.13613;-0.92869;,
 -9.17830;-0.94781;-0.80177;,
 -9.26161;-0.97942;0.11040;,
 -9.26567;-0.08023;0.05962;,
 -7.20925;-1.98464;-0.80213;,
 -6.00680;-1.98050;-0.82282;,
 -6.14017;-2.16570;0.13280;,
 -7.49087;-2.17035;0.15604;,
 -0.33898;-1.02656;-1.05511;,
 -0.34549;-0.12588;-1.24495;,
 -0.32552;-0.06079;-0.09418;,
 -0.32077;-1.10786;-0.03504;,
 -7.53781;-0.20847;-2.12368;,
 -5.73927;-0.20229;-2.15463;,
 -5.42339;-1.08798;-1.93471;,
 -7.78424;-0.89497;-1.90546;,
 -7.25650;-0.86919;2.08182;,
 -6.01461;-0.86490;2.06045;,
 -6.11193;0.04132;2.18607;,
 -6.95969;0.23254;2.18968;,
 -1.62129;1.89259;-1.11650;,
 -3.21340;1.88712;-1.08911;,
 -3.19104;2.17813;-0.16308;,
 -1.60050;2.18361;-0.19044;,
 -1.48460;-1.07437;-2.00246;,
 -3.15551;-1.08014;-1.97372;,
 -3.15377;-0.19335;-2.19911;,
 -1.49541;-0.18762;-2.22764;,
 -1.70092;-2.15037;0.05643;,
 -3.13806;-2.15533;0.08115;,
 -3.18077;-1.97076;-0.87144;,
 -1.22793;-1.96402;-0.90504;,
 -3.10182;-0.85486;2.01036;,
 -1.44717;-0.84914;1.98189;,
 -1.48779;0.56704;2.07766;,
 -3.11206;0.41825;2.11372;,
 -0.71783;1.95155;-0.28489;,
 -0.72913;1.66469;-0.98425;,
 -1.49541;-0.18762;-2.22764;,
 -0.74071;-0.16328;-2.01119;,
 -0.73341;-0.87505;-1.73760;,
 -1.48460;-1.07437;-2.00246;,
 -0.69874;-1.91702;0.02666;,
 -1.70092;-2.15037;0.05643;,
 -1.22793;-1.96402;-0.90504;,
 -0.71387;-1.71607;-0.79326;,
 -1.44717;-0.84914;1.98189;,
 -0.29659;-0.56487;1.37476;,
 -0.29593;0.05123;1.53479;,
 -1.48779;0.56704;2.07766;,
 -8.87652;-1.67172;0.15244;,
 -8.71349;-1.56713;-0.61597;,
 -8.91255;-0.16562;-1.59769;,
 -7.53781;-0.20847;-2.12368;,
 -7.78424;-0.89497;-1.90546;,
 -8.74014;-0.84102;-1.42336;,
 -8.89156;1.65517;-0.03549;,
 -7.51673;2.14269;-0.45135;,
 -6.88402;1.87444;-1.02597;,
 -8.72716;1.46612;-0.78730;,
 -8.68722;-0.66852;1.62593;,
 -8.85481;0.02258;1.72872;,
 -0.30169;0.01682;1.27818;,
 -0.30056;-0.87498;1.16353;,
 -0.32077;-1.10786;-0.03504;,
 -0.32552;-0.06079;-0.09418;,
 -0.68341;-1.56979;0.97253;,
 -1.54520;-1.80400;1.15983;,
 -1.70092;-2.15037;0.05643;,
 -0.69874;-1.91702;0.02666;,
 -3.14999;-1.80954;1.18743;,
 -3.13806;-2.15533;0.08115;,
 -5.94291;-1.81919;1.23548;,
 -7.11760;-1.82324;1.25569;,
 -8.65160;-1.44551;1.04258;,
 -9.12526;-0.81991;1.18345;,
 -9.24523;-0.01356;1.23822;,
 -8.66503;1.53261;0.87435;,
 -7.79325;1.94317;1.05413;,
 -7.79325;1.94317;1.05413;,
 -5.95992;1.94950;1.02259;,
 -3.17878;1.95909;0.97475;,
 -1.58640;1.96457;0.94735;,
 -0.69826;1.71846;0.78678;,
 -9.12325;0.92741;1.07623;,
 -9.27039;0.97265;0.00013;,
 -9.17779;0.83270;-0.89545;,
 -8.73252;0.65615;-1.49636;,
 -7.92874;0.65764;-1.97595;,
 -7.92874;0.65764;-1.97595;,
 -5.47308;0.87427;-2.02995;,
 -3.16481;0.88221;-2.06968;,
 -1.49286;0.88799;-2.09844;,
 -1.49286;0.88799;-2.09844;,
 -0.74025;0.71984;-1.80788;,
 -0.34772;0.95825;-1.15543;,
 -0.33108;1.16516;-0.16343;,
 -0.30955;1.05416;1.04055;,
 -0.33108;1.16516;-0.16343;,
 -1.48779;0.56704;2.07766;,
 -0.29593;0.05123;1.53479;,
 -0.68180;0.91036;1.56059;,
 -1.45310;1.11157;1.85619;,
 -3.11032;1.10584;1.88471;,
 -3.11206;0.41825;2.11372;,
 -6.95969;0.23254;2.18968;,
 -6.11193;0.04132;2.18607;,
 -6.01557;1.09582;1.93468;,
 -7.24819;1.09158;1.95588;,
 -7.24819;1.09158;1.95588;,
 -8.67999;0.82729;1.52938;,
 -4.73503;-0.19879;-2.17191;,
 -5.34334;-1.08772;-1.93608;,
 -4.75908;0.87670;-2.04225;,
 -4.70766;2.17288;-0.13698;,
 -4.72586;1.90025;-0.73810;,
 -4.69715;1.95384;1.00087;,
 -4.92611;0.04538;2.16566;,
 -4.69047;1.10040;1.91188;,
 -4.67960;-0.86030;2.03749;,
 -4.92611;0.04538;2.16566;,
 -4.25825;-1.81338;1.20649;,
 -4.57338;-2.17689;-0.18783;,
 -4.98807;-1.97699;-0.84035;,
 -4.57338;-2.17689;-0.18783;,
 -4.69715;1.95384;1.00087;,
 -4.70766;2.17288;-0.13698;,
 -4.72586;1.90025;-0.73810;,
 -5.47308;0.87427;-2.02995;,
 -4.75908;0.87670;-2.04225;,
 -4.73503;-0.19879;-2.17191;,
 -5.73927;-0.20229;-2.15463;,
 -5.34334;-1.08772;-1.93608;,
 -5.42339;-1.08798;-1.93471;,
 -5.73927;-0.20229;-2.15463;,
 -4.73503;-0.19879;-2.17191;,
 -4.57338;-2.17689;-0.18783;,
 -4.98807;-1.97699;-0.84035;,
 -4.25825;-1.81338;1.20649;,
 -4.67960;-0.86030;2.03749;,
 -4.69047;1.10040;1.91188;,
 -4.92611;0.04538;2.16566;,
 -6.61304;1.40092;-1.54645;,
 -8.73252;0.65615;-1.49636;,
 -8.58969;1.30804;-1.41602;,
 -5.07619;1.40623;-1.57289;,
 -4.69204;1.40756;-1.57949;,
 -4.75908;0.87670;-2.04225;,
 -5.47308;0.87427;-2.02995;,
 -5.07619;1.40623;-1.57289;,
 -3.02662;1.71994;-1.62551;,
 -3.16481;0.88221;-2.06968;,
 -4.75908;0.87670;-2.04225;,
 -4.69204;1.40756;-1.57949;,
 -2.02181;1.79486;-1.64682;,
 -1.49286;0.88799;-2.09844;,
 -0.73990;1.42042;-1.64660;,
 -2.02181;1.79486;-1.64682;,
 -0.71783;1.95155;-0.28489;,
 -0.72913;1.66469;-0.98425;,
 -0.69826;1.71846;0.78678;,
 -0.71783;1.95155;-0.28489;,
 -0.68839;1.58830;1.32145;,
 -1.96858;1.58476;1.34425;,
 -3.33634;1.58004;1.36779;,
 -4.64048;1.57555;1.39023;,
 -5.63572;1.57209;1.40735;,
 -4.64048;1.57555;1.39023;,
 -7.38875;1.56603;1.43751;,
 -7.38875;1.56603;1.43751;,
 -8.54136;1.46572;1.37125;,
 -0.68341;-1.56979;0.97253;,
 -0.69874;-1.91702;0.02666;,
 -0.71387;-1.71607;-0.79326;,
 -0.69874;-1.91702;0.02666;,
 -0.72650;-1.54806;-1.47891;,
 -1.31001;-1.55094;-1.46968;,
 -3.37446;-1.55808;-1.43416;,
 -1.31001;-1.55094;-1.46968;,
 -5.16075;-1.58093;-1.69887;,
 -5.83976;-1.75389;-1.55902;,
 -5.34334;-1.08772;-1.93608;,
 -5.16075;-1.58093;-1.69887;,
 -6.87599;-1.75745;-1.54120;,
 -8.74014;-0.84102;-1.42336;,
 -8.57708;-1.47965;-1.25854;,
 -6.54812;-1.40119;1.59107;,
 -8.52878;-1.32195;1.52872;,
 -5.62234;-1.39802;1.57513;,
 -4.62708;-1.39460;1.55802;,
 -3.32292;-1.39008;1.53556;,
 -4.62708;-1.39460;1.55802;,
 -1.95515;-1.38537;1.51202;,
 -0.67499;-1.38015;1.48914;,
 -1.95515;-1.38537;1.51202;,
 -0.68180;0.91036;1.56059;,
 -0.68839;1.58830;1.32145;,
 -0.29593;0.05123;1.53479;,
 -0.29659;-0.56487;1.37476;,
 -0.67499;-1.38015;1.48914;,
 -0.68341;-1.56979;0.97253;,
 -0.30056;-0.87498;1.16353;,
 -0.29659;-0.56487;1.37476;,
 -1.95515;-1.38537;1.51202;,
 -1.54520;-1.80400;1.15983;,
 -0.68341;-1.56979;0.97253;,
 -0.67499;-1.38015;1.48914;,
 -3.32292;-1.39008;1.53556;,
 -3.14999;-1.80954;1.18743;,
 -1.54520;-1.80400;1.15983;,
 -1.95515;-1.38537;1.51202;,
 -4.62708;-1.39460;1.55802;,
 -4.25825;-1.81338;1.20649;,
 -5.62234;-1.39802;1.57513;,
 -4.62708;-1.39460;1.55802;,
 -6.54812;-1.40119;1.59107;,
 -8.52878;-1.32195;1.52872;,
 -8.68722;-0.66852;1.62593;,
 -8.85481;0.02258;1.72872;,
 -8.67999;0.82729;1.52938;,
 -3.37446;-1.55808;-1.43416;,
 -5.16075;-1.58093;-1.69887;,
 -1.31001;-1.55094;-1.46968;,
 -1.31001;-1.55094;-1.46968;,
 -0.72650;-1.54806;-1.47891;,
 -0.73341;-0.87505;-1.73760;,
 -0.72650;-1.54806;-1.47891;,
 -0.74071;-0.16328;-2.01119;,
 -0.74025;0.71984;-1.80788;,
 -0.72913;1.66469;-0.98425;,
 -0.34772;0.95825;-1.15543;,
 -0.74025;0.71984;-1.80788;,
 -0.73990;1.42042;-1.64660;,
 -0.73990;1.42042;-1.64660;,
 -2.02181;1.79486;-1.64682;,
 -3.02662;1.71994;-1.62551;,
 -4.69204;1.40756;-1.57949;,
 -6.02419;1.87741;-1.04075;,
 -8.73252;0.65615;-1.49636;,
 -8.91255;-0.16562;-1.59769;,
 -9.28283;-0.13613;-0.92869;,
 -9.17779;0.83270;-0.89545;,
 -8.73252;0.65615;-1.49636;,
 -8.74014;-0.84102;-1.42336;,
 -9.17830;-0.94781;-0.80177;,
 -8.74014;-0.84102;-1.42336;,
 -8.57708;-1.47965;-1.25854;,
 -6.87599;-1.75745;-1.54120;,
 -5.83976;-1.75389;-1.55902;,
 -5.16075;-1.58093;-1.69887;;
 
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
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;11,54,55,8;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,20,23,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;71,74,75,72;,
 4;76,77,11,10;,
 4;77,78,54,11;,
 4;79,80,7,6;,
 4;81,82,61,60;,
 4;83,84,1,0;,
 4;85,86,27,26;,
 4;86,87,40,27;,
 4;80,88,89,7;,
 4;90,4,7,89;,
 4;91,92,57,56;,
 4;93,94,17,16;,
 4;95,96,31,30;,
 4;97,98,43,42;,
 4;13,99,100,14;,
 4;101,66,69,102;,
 4;103,104,105,106;,
 4;106,107,108,103;,
 4;109,110,111,112;,
 4;65,23,113,114;,
 4;115,30,29,116;,
 4;117,95,30,115;,
 4;118,26,25,119;,
 4;120,85,26,118;,
 4;121,108,107,122;,
 4;123,36,39,124;,
 4;74,125,126,75;,
 4;127,34,33,128;,
 4;84,129,130,1;,
 4;131,2,1,130;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,10,9,141;,
 4;142,76,10,140;,
 4;21,143,121,22;,
 4;144,111,110,145;,
 4;88,81,60,89;,
 4;63,90,89,60;,
 4;146,93,147,148;,
 4;149,94,93,146;,
 4;150,151,152,153;,
 4;154,155,156,157;,
 4;158,159,155,154;,
 4;160,98,97,161;,
 4;162,100,99,163;,
 4;164,101,102,165;,
 4;106,105,166,167;,
 4;168,107,106,167;,
 4;122,107,168,169;,
 4;170,111,144,171;,
 4;112,111,170,172;,
 4;114,113,173,174;,
 4;67,175,176,68;,
 4;177,12,15,178;,
 4;45,44,179,180;,
 4;181,29,28,182;,
 4;116,29,181,183;,
 4;184,18,185,186;,
 4;19,18,184,187;,
 4;188,19,187,189;,
 4;54,6,5,55;,
 4;78,79,6,54;,
 4;190,20,64,191;,
 4;192,21,20,190;,
 4;193,143,21,192;,
 4;194,36,123,195;,
 4;196,37,36,194;,
 4;197,51,50,198;,
 4;199,101,164,200;,
 4;201,66,101,199;,
 4;202,67,66,201;,
 4;203,204,205,206;,
 4;207,208,209,210;,
 4;211,212,213,214;,
 4;215,216,212,211;,
 4;217,76,142,218;,
 4;219,77,76,217;,
 4;220,78,77,219;,
 4;221,79,78,220;,
 4;222,80,79,221;,
 4;223,88,80,222;,
 4;174,81,88,223;,
 4;173,82,81,174;,
 4;170,84,83,172;,
 4;171,129,84,170;,
 4;168,85,120,169;,
 4;167,86,85,168;,
 4;166,87,86,167;,
 4;224,34,127,225;,
 4;35,34,224,226;,
 4;49,48,227,228;,
 4;229,12,177,230;,
 4;231,13,12,229;,
 4;232,99,13,231;,
 4;233,234,235,236;,
 4;24,41,237,238;,
 4;239,25,24,238;,
 4;119,25,239,240;,
 4;149,241,119,240;,
 4;62,241,149,146;,
 4;63,62,146,148;,
 4;242,90,63,148;,
 4;243,244,245,246;,
 4;247,248,244,243;,
 4;55,5,249,250;,
 4;8,55,250,251;,
 4;252,9,8,251;,
 4;141,9,252,253;;
 
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
    "data\\TEXTURE\\cat_color.jpg";
   }
  }
 }
 MeshNormals {
  131;
  0.444491;0.659114;0.606627;,
  0.527835;0.593623;-0.607455;,
  -0.427090;0.635853;0.642873;,
  -0.443422;0.608180;-0.658403;,
  -0.374209;-0.609333;0.699058;,
  -0.485390;-0.678163;-0.551807;,
  0.472467;-0.599856;0.645715;,
  0.483042;-0.644031;-0.593208;,
  0.009269;0.728438;0.685049;,
  -0.045344;0.761576;-0.646487;,
  0.028200;-0.743666;-0.667957;,
  0.015302;-0.651049;0.758881;,
  0.101814;0.730018;0.675801;,
  0.129627;0.742451;-0.657239;,
  0.109453;-0.754239;-0.647413;,
  0.120692;-0.642981;0.756313;,
  -0.084548;-0.655096;0.750800;,
  -0.168220;-0.762635;-0.624572;,
  -0.135272;0.676879;-0.723558;,
  -0.126200;0.710886;0.691892;,
  0.632066;0.772102;-0.065965;,
  0.653109;-0.755929;0.044946;,
  0.162933;-0.984468;0.065393;,
  0.003132;-0.999763;0.021528;,
  -0.157279;-0.985872;0.057616;,
  -0.607884;-0.792151;0.054541;,
  -0.629320;0.770025;-0.104962;,
  -0.179154;0.973996;-0.138696;,
  -0.004014;0.996285;-0.086028;,
  0.135618;0.988521;-0.066583;,
  -0.523424;0.043533;0.850960;,
  -0.999826;-0.006191;0.017594;,
  -0.653786;-0.060133;-0.754286;,
  -0.230479;-0.071181;-0.970470;,
  -0.016940;-0.064585;-0.997768;,
  0.158927;-0.064330;-0.985192;,
  0.645347;-0.048298;-0.762361;,
  0.999840;0.003536;-0.017550;,
  0.807750;0.121595;0.576849;,
  0.240935;0.102722;0.965090;,
  0.016872;0.068550;0.997505;,
  -0.129980;0.063879;0.989457;,
  0.016159;-0.764402;-0.644538;,
  -0.016941;-0.064587;-0.997768;,
  -0.076966;0.768750;-0.634901;,
  -0.011484;0.997346;-0.071893;,
  0.009275;0.728439;0.685048;,
  0.015076;0.114065;0.993359;,
  0.015308;-0.651050;0.758880;,
  0.005234;-0.999286;0.037410;,
  0.009267;0.728435;0.685052;,
  0.007103;0.996180;-0.087034;,
  -0.005545;0.723877;-0.689906;,
  -0.021758;-0.066197;-0.997569;,
  -0.001024;-0.752061;-0.659093;,
  0.002305;-0.999199;0.039958;,
  0.015296;-0.651044;0.758886;,
  0.017631;0.057984;0.998162;,
  -0.509088;0.394436;0.765016;,
  -0.949611;0.313427;-0.001539;,
  -0.612564;0.298606;-0.731846;,
  -0.210180;0.337095;-0.917710;,
  -0.026451;0.400541;-0.915897;,
  -0.029958;0.381878;-0.923727;,
  -0.034718;0.324672;-0.945189;,
  0.139592;0.282811;-0.948964;,
  0.631890;0.251888;-0.732985;,
  0.969343;0.243454;-0.033229;,
  0.657189;0.408083;0.633697;,
  0.175898;0.491693;0.852817;,
  0.004782;0.543333;0.839503;,
  0.008095;0.517682;0.855535;,
  0.018163;0.510959;0.859413;,
  -0.119286;0.450403;0.884821;,
  0.564714;-0.350731;0.747051;,
  0.972088;-0.234589;-0.003590;,
  0.618477;-0.352340;-0.702384;,
  0.130284;-0.463017;-0.876722;,
  0.001454;-0.480183;-0.877167;,
  -0.006426;-0.395381;-0.918495;,
  -0.027957;-0.357252;-0.933590;,
  -0.202526;-0.364972;-0.908724;,
  -0.607058;-0.383730;-0.695867;,
  -0.946202;-0.321750;0.034341;,
  -0.495307;-0.332883;0.802409;,
  -0.115027;-0.358034;0.926596;,
  0.012603;-0.414775;0.909837;,
  0.021898;-0.412247;0.910809;,
  0.023416;-0.398064;0.917059;,
  0.198940;-0.339640;0.919276;,
  0.596288;0.742339;0.305571;,
  0.935213;0.304463;0.180774;,
  0.995253;0.078897;0.056981;,
  0.968974;-0.225780;0.100562;,
  0.599750;-0.715842;0.357589;,
  0.120811;-0.856394;0.501990;,
  0.006942;-0.832069;0.554629;,
  0.012653;-0.835962;0.548641;,
  0.018187;-0.833093;0.552834;,
  -0.113973;-0.847645;0.518178;,
  -0.525382;-0.713564;0.463466;,
  -0.847816;-0.336684;0.409699;,
  -0.919347;0.011225;0.393288;,
  -0.852785;0.362929;0.375552;,
  -0.574592;0.737108;0.355690;,
  -0.174611;0.903479;0.391454;,
  -0.001499;0.890784;0.454424;,
  0.004882;0.886944;0.461850;,
  0.004887;0.886943;0.461854;,
  0.116963;0.907804;0.402755;,
  0.024337;-0.940236;-0.339654;,
  0.013086;-0.920467;-0.390601;,
  0.149271;-0.925114;-0.349116;,
  0.639027;-0.718291;-0.275141;,
  0.938313;-0.247715;-0.241258;,
  0.965199;-0.012939;-0.261196;,
  0.936405;0.222240;-0.271579;,
  0.620523;0.709414;-0.334190;,
  0.118205;0.942869;-0.311489;,
  -0.058387;0.940383;-0.335069;,
  -0.028124;0.907962;-0.418107;,
  0.022280;0.878553;-0.477125;,
  -0.121548;0.854327;-0.505323;,
  -0.555466;0.698222;-0.451601;,
  -0.888449;0.306148;-0.341953;,
  -0.953169;-0.027389;-0.301197;,
  -0.884061;-0.359392;-0.298787;,
  -0.566986;-0.769834;-0.293058;,
  -0.141557;-0.957347;-0.251892;,
  0.009076;-0.962786;-0.270113;,
  0.999694;0.004734;-0.024277;;
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
  4;130,93,92,38;,
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
  254;
  0.500060;0.098590;,
  0.500060;0.105500;,
  0.516010;0.105500;,
  0.516010;0.098590;,
  0.516010;0.905670;,
  0.516010;0.891160;,
  0.500060;0.891160;,
  0.500060;0.905670;,
  0.516010;0.861290;,
  0.516010;0.854380;,
  0.500060;0.854380;,
  0.500060;0.861290;,
  0.516010;0.495350;,
  0.516010;0.480840;,
  0.500060;0.480840;,
  0.500060;0.495350;,
  0.559810;0.952290;,
  0.559810;0.959210;,
  0.574320;0.959210;,
  0.574320;0.952290;,
  0.425680;0.952290;,
  0.425680;0.959210;,
  0.440190;0.959210;,
  0.440190;0.952290;,
  0.516010;0.984470;,
  0.516010;0.975340;,
  0.500060;0.975340;,
  0.500060;0.984470;,
  0.574320;0.588520;,
  0.574320;0.579390;,
  0.559810;0.579390;,
  0.559810;0.588520;,
  0.500060;0.433170;,
  0.500060;0.442290;,
  0.516010;0.442290;,
  0.516010;0.433170;,
  0.425680;0.499380;,
  0.425680;0.508510;,
  0.440190;0.508510;,
  0.440190;0.499380;,
  0.500060;0.994830;,
  0.516010;0.994830;,
  0.559810;0.570550;,
  0.559810;0.580910;,
  0.574320;0.580910;,
  0.574320;0.570550;,
  0.500060;0.404840;,
  0.500060;0.415200;,
  0.516010;0.415200;,
  0.516010;0.404840;,
  0.425680;0.568950;,
  0.425680;0.579310;,
  0.440190;0.579310;,
  0.440190;0.568950;,
  0.500060;0.877450;,
  0.516010;0.877450;,
  0.559810;0.210900;,
  0.559810;0.227050;,
  0.574320;0.227050;,
  0.574320;0.210900;,
  0.500060;0.936140;,
  0.500060;0.952290;,
  0.516010;0.952290;,
  0.516010;0.936140;,
  0.425680;0.936140;,
  0.440190;0.936140;,
  0.481040;0.790530;,
  0.481040;0.805040;,
  0.500060;0.805040;,
  0.500060;0.790530;,
  0.481040;0.562660;,
  0.481040;0.573020;,
  0.500060;0.573020;,
  0.500060;0.562660;,
  0.481040;0.582150;,
  0.500060;0.582150;,
  0.481040;0.854380;,
  0.481040;0.861290;,
  0.481040;0.877450;,
  0.481040;0.891160;,
  0.481040;0.905670;,
  0.481040;0.936140;,
  0.481040;0.952290;,
  0.481040;0.098590;,
  0.481040;0.105500;,
  0.481040;0.975340;,
  0.481040;0.984470;,
  0.481040;0.994830;,
  0.481040;0.922660;,
  0.500060;0.922660;,
  0.516010;0.922660;,
  0.542820;0.210900;,
  0.542820;0.227050;,
  0.542820;0.952290;,
  0.542820;0.959210;,
  0.542820;0.579390;,
  0.542820;0.588520;,
  0.542820;0.570550;,
  0.542820;0.580910;,
  0.516010;0.463850;,
  0.500060;0.463850;,
  0.481040;0.773540;,
  0.500060;0.773540;,
  0.440190;0.984470;,
  0.440190;0.994830;,
  0.457180;0.994830;,
  0.457180;0.984470;,
  0.457180;0.975340;,
  0.440190;0.975340;,
  0.440190;0.098590;,
  0.440190;0.105500;,
  0.457180;0.105500;,
  0.457180;0.098590;,
  0.457180;0.952290;,
  0.457180;0.936140;,
  0.559810;0.570690;,
  0.574320;0.570690;,
  0.542820;0.570690;,
  0.500060;0.966640;,
  0.516010;0.966640;,
  0.481040;0.966640;,
  0.440190;0.966640;,
  0.457180;0.966640;,
  0.425680;0.490680;,
  0.440190;0.490680;,
  0.481040;0.590860;,
  0.500060;0.590860;,
  0.516010;0.451000;,
  0.500060;0.451000;,
  0.481040;0.112930;,
  0.500060;0.112930;,
  0.516010;0.112930;,
  0.542820;0.483250;,
  0.542820;0.490680;,
  0.559810;0.490680;,
  0.559810;0.483250;,
  0.574320;0.475300;,
  0.574320;0.467870;,
  0.559810;0.467870;,
  0.559810;0.475300;,
  0.500060;0.846950;,
  0.516010;0.846950;,
  0.481040;0.846950;,
  0.425680;0.966640;,
  0.457180;0.112930;,
  0.440190;0.112930;,
  0.529340;0.952290;,
  0.542820;0.936140;,
  0.529340;0.936140;,
  0.529340;0.959210;,
  0.529340;0.475300;,
  0.542820;0.475300;,
  0.542820;0.467870;,
  0.529340;0.467870;,
  0.529340;0.506940;,
  0.542820;0.506940;,
  0.542820;0.498230;,
  0.529340;0.498230;,
  0.529340;0.516070;,
  0.542820;0.516070;,
  0.529340;0.580910;,
  0.529340;0.570550;,
  0.500060;0.450370;,
  0.516010;0.450370;,
  0.481040;0.760070;,
  0.500060;0.760070;,
  0.470650;0.994830;,
  0.470650;0.984470;,
  0.470650;0.975340;,
  0.470650;0.966640;,
  0.470650;0.105500;,
  0.470650;0.112930;,
  0.470650;0.098590;,
  0.470650;0.952290;,
  0.470650;0.936140;,
  0.481040;0.818760;,
  0.500060;0.818760;,
  0.516010;0.509060;,
  0.500060;0.509060;,
  0.588040;0.580910;,
  0.588040;0.570550;,
  0.588040;0.579390;,
  0.588040;0.588520;,
  0.588040;0.570690;,
  0.588040;0.959210;,
  0.574320;0.966640;,
  0.588040;0.966640;,
  0.588040;0.952290;,
  0.574320;0.936140;,
  0.588040;0.936140;,
  0.411960;0.952290;,
  0.411960;0.936140;,
  0.411960;0.959210;,
  0.411960;0.966640;,
  0.411960;0.499380;,
  0.411960;0.490680;,
  0.411960;0.508510;,
  0.411960;0.579310;,
  0.411960;0.568950;,
  0.470650;0.773540;,
  0.470650;0.760070;,
  0.470650;0.790530;,
  0.470650;0.805040;,
  0.470650;0.478780;,
  0.481040;0.478780;,
  0.481040;0.465070;,
  0.470650;0.465070;,
  0.470650;0.413590;,
  0.481040;0.413590;,
  0.481040;0.403240;,
  0.470650;0.403240;,
  0.470650;0.362280;,
  0.481040;0.362280;,
  0.481040;0.353160;,
  0.470650;0.353160;,
  0.470650;0.370990;,
  0.481040;0.370990;,
  0.470650;0.854380;,
  0.470650;0.846950;,
  0.470650;0.861290;,
  0.470650;0.877450;,
  0.470650;0.891160;,
  0.470650;0.905670;,
  0.470650;0.922660;,
  0.529340;0.442290;,
  0.529340;0.451000;,
  0.529340;0.433170;,
  0.529340;0.415200;,
  0.529340;0.404840;,
  0.529340;0.495350;,
  0.529340;0.509060;,
  0.529340;0.480840;,
  0.529340;0.463850;,
  0.516010;0.557570;,
  0.516010;0.571050;,
  0.529340;0.571050;,
  0.529340;0.557570;,
  0.529340;0.994830;,
  0.529340;0.984470;,
  0.529340;0.975340;,
  0.529340;0.966640;,
  0.516010;0.959210;,
  0.529340;0.922660;,
  0.529340;0.180430;,
  0.516010;0.180430;,
  0.516010;0.197420;,
  0.529340;0.197420;,
  0.529340;0.165930;,
  0.516010;0.165930;,
  0.529340;0.891160;,
  0.529340;0.877450;,
  0.529340;0.861290;,
  0.529340;0.854380;,
  0.529340;0.846950;;
 }
}
