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
 256;
 -11.65783;0.77925;-7.69885;,
 -13.55982;0.77925;-7.69885;,
 -13.55982;15.54569;-7.69885;,
 -11.65783;15.54569;-7.69885;,
 -13.55982;15.54569;7.69885;,
 -11.65783;15.54569;7.69885;,
 -13.55982;0.77925;7.69885;,
 -11.65783;0.77925;7.69885;,
 -13.55982;0.77925;-7.69885;,
 -11.65783;0.77925;-7.69885;,
 -13.55982;0.77925;-7.69885;,
 -13.55982;0.77925;7.69885;,
 -13.55982;15.54569;7.69885;,
 -13.55982;15.54569;-7.69885;,
 -11.65783;0.77925;7.69885;,
 -11.65783;15.54569;7.69885;,
 12.78777;1.13277;-7.05243;,
 -12.87932;1.13277;-7.05243;,
 -12.87932;15.54569;-7.05243;,
 12.78777;15.54569;-7.05243;,
 -12.87932;15.54569;7.05243;,
 12.78777;15.54569;7.05243;,
 -12.87932;1.13277;7.05243;,
 12.78777;1.13277;7.05243;,
 -12.87932;1.13277;-7.05243;,
 12.78777;1.13277;-7.05243;,
 -12.87932;1.13277;7.05243;,
 -12.87932;15.54569;7.05243;,
 12.78777;1.13277;7.05243;,
 12.78777;15.54569;7.05243;,
 13.38443;0.77925;-7.69885;,
 11.48243;0.77925;-7.69885;,
 11.48243;15.54569;-7.69885;,
 13.38443;15.54569;-7.69885;,
 11.48243;15.54569;7.69885;,
 13.38443;15.54569;7.69885;,
 11.48243;0.77925;7.69885;,
 13.38443;0.77925;7.69885;,
 11.48243;0.77925;-7.69885;,
 13.38443;0.77925;-7.69885;,
 11.48243;0.77925;7.69885;,
 11.48243;15.54569;7.69885;,
 13.38443;0.77925;7.69885;,
 13.38443;0.77925;-7.69885;,
 13.38443;15.54569;-7.69885;,
 13.38443;15.54569;7.69885;,
 0.90667;0.77925;-7.69885;,
 -0.99532;0.77925;-7.69885;,
 -0.99532;15.54569;-7.69885;,
 0.90667;15.54569;-7.69885;,
 -0.99532;15.54569;7.69885;,
 0.90667;15.54569;7.69885;,
 -0.99532;0.77925;7.69885;,
 0.90667;0.77925;7.69885;,
 -0.99532;0.77925;-7.69885;,
 0.90667;0.77925;-7.69885;,
 -0.99532;0.77925;7.69885;,
 -0.99532;15.54569;7.69885;,
 0.90667;0.77925;7.69885;,
 0.90667;15.54569;7.69885;,
 0.90354;23.23680;1.43753;,
 -0.90750;23.23681;1.45222;,
 -0.89693;22.06401;5.87693;,
 0.89929;22.06401;5.86224;,
 0.89749;18.58301;7.72528;,
 0.90354;18.58301;1.43753;,
 0.90347;20.48321;1.51995;,
 0.89796;20.48321;7.23703;,
 -0.89000;15.48918;7.73995;,
 -0.90502;15.48918;1.45222;,
 0.90354;15.48918;1.43753;,
 0.89749;15.48918;7.72528;,
 0.89796;20.48321;7.23703;,
 -0.89164;20.48321;7.25170;,
 -0.89000;18.58301;7.73995;,
 0.89749;18.58301;7.72528;,
 0.91247;18.58301;-7.83492;,
 -0.92716;18.58301;-7.82021;,
 -0.92645;20.48321;-7.32679;,
 0.91199;20.48321;-7.34150;,
 0.91247;15.48918;-7.83491;,
 0.90638;15.48918;-1.50836;,
 -0.91205;15.48918;-1.49367;,
 -0.92716;15.48918;-7.82020;,
 0.91199;20.48321;-7.34150;,
 0.90647;20.48321;-1.60325;,
 0.90638;18.58301;-1.50836;,
 0.91247;18.58301;-7.83492;,
 -0.92517;22.06401;-5.94609;,
 -0.91460;23.23681;-1.52273;,
 0.90641;23.23681;-1.53744;,
 0.91066;22.06401;-5.96081;,
 -0.89000;15.48918;7.73995;,
 0.89749;15.48918;7.72528;,
 0.91247;15.48918;-7.83491;,
 -0.92716;15.48918;-7.82020;,
 -0.89693;22.06401;5.87693;,
 0.89929;22.06401;5.86224;,
 -0.92517;22.06401;-5.94609;,
 0.91066;22.06401;-5.96081;,
 -12.96411;19.90084;7.11862;,
 -13.09987;19.90084;1.72256;,
 -13.10010;18.14921;1.64476;,
 -13.08279;18.14921;7.58005;,
 12.92221;22.43914;1.52048;,
 0.07091;22.43914;1.58435;,
 0.08309;21.35804;5.76104;,
 12.92221;21.35804;5.69717;,
 12.92221;18.14921;7.45578;,
 12.92221;18.14921;1.52049;,
 12.92221;19.90084;1.59828;,
 12.92221;19.90084;6.99490;,
 0.10427;15.29727;7.51957;,
 0.08696;15.29727;1.58428;,
 12.92221;15.29727;1.52049;,
 12.92221;15.29727;7.45578;,
 12.92221;19.90084;6.99490;,
 0.09986;19.90084;7.05870;,
 0.10427;18.14921;7.51957;,
 12.92221;18.14921;7.45578;,
 12.92221;18.14921;-7.23219;,
 0.06143;18.14921;-7.16840;,
 0.05973;19.90084;-6.70262;,
 12.92221;19.90084;-6.76643;,
 12.92221;15.29727;-7.23218;,
 12.92221;15.29727;-1.26027;,
 0.07885;15.29727;-1.19648;,
 0.06143;15.29727;-7.16839;,
 12.92221;19.90084;-6.76643;,
 12.92221;19.90084;-1.34984;,
 12.92221;18.14921;-1.26027;,
 12.92221;18.14921;-7.23219;,
 0.05054;21.35804;-5.39927;,
 0.06272;22.43915;-1.22385;,
 12.92221;22.43915;-1.28771;,
 12.92221;21.35804;-5.46313;,
 -13.12563;18.14921;-7.10792;,
 -13.10821;18.14921;-1.13600;,
 -13.10847;19.90084;-1.22557;,
 -13.12426;19.90084;-6.64216;,
 -13.12046;21.35804;-5.33886;,
 -13.10829;22.43915;-1.16344;,
 -13.10009;22.43914;1.64475;,
 -13.08791;21.35804;5.82144;,
 -13.10010;15.29727;1.64476;,
 -13.24920;15.29727;7.58080;,
 -13.10821;15.29727;-1.13600;,
 -13.12563;15.29727;-7.10791;,
 -13.12563;15.29727;-7.10791;,
 -13.10821;15.29727;-1.13600;,
 -13.10010;15.29727;1.64476;,
 -13.24920;15.29727;7.58080;,
 0.10427;15.29727;7.51957;,
 12.92221;15.29727;7.45578;,
 12.92221;15.29727;-7.23218;,
 0.06143;15.29727;-7.16839;,
 0.08309;21.35804;5.76104;,
 12.92221;21.35804;5.69717;,
 0.05054;21.35804;-5.39927;,
 12.92221;21.35804;-5.46313;,
 13.35394;23.23680;1.43753;,
 11.54290;23.23681;1.45222;,
 11.55346;22.06401;5.87693;,
 13.34968;22.06401;5.86224;,
 13.34789;18.58301;7.72528;,
 13.35394;18.58301;1.43753;,
 13.35386;20.48321;1.51995;,
 13.34836;20.48321;7.23703;,
 11.56039;15.48918;7.73995;,
 11.54538;15.48918;1.45222;,
 13.35394;15.48918;1.43753;,
 13.34789;15.48918;7.72528;,
 13.34836;20.48321;7.23703;,
 11.55876;20.48321;7.25170;,
 11.56039;18.58301;7.73995;,
 13.34789;18.58301;7.72528;,
 13.36286;18.58301;-7.83492;,
 11.52324;18.58301;-7.82021;,
 11.52394;20.48321;-7.32679;,
 13.36239;20.48321;-7.34150;,
 13.36286;15.48918;-7.83491;,
 13.35678;15.48918;-1.50836;,
 11.53835;15.48918;-1.49367;,
 11.52324;15.48918;-7.82020;,
 13.36239;20.48321;-7.34150;,
 13.35687;20.48321;-1.60325;,
 13.35678;18.58301;-1.50836;,
 13.36286;18.58301;-7.83492;,
 11.52523;22.06401;-5.94609;,
 11.53579;23.23681;-1.52273;,
 13.35680;23.23681;-1.53744;,
 13.36106;22.06401;-5.96081;,
 11.56039;15.48918;7.73995;,
 13.34789;15.48918;7.72528;,
 13.35394;15.48918;1.43753;,
 13.34789;15.48918;7.72528;,
 13.35678;15.48918;-1.50836;,
 13.36286;15.48918;-7.83491;,
 13.36286;15.48918;-7.83491;,
 11.52324;15.48918;-7.82020;,
 13.36106;22.06401;-5.96081;,
 13.35680;23.23681;-1.53744;,
 13.35394;23.23680;1.43753;,
 13.34968;22.06401;5.86224;,
 11.55346;22.06401;5.87693;,
 13.34968;22.06401;5.86224;,
 11.52523;22.06401;-5.94609;,
 13.36106;22.06401;-5.96081;,
 -13.61328;23.23680;-1.52550;,
 -11.80224;23.23681;-1.54020;,
 -11.81280;22.06401;-5.96490;,
 -13.60902;22.06401;-5.95022;,
 -13.60723;18.58301;-7.81326;,
 -13.61328;18.58301;-1.52551;,
 -13.61320;20.48321;-1.60792;,
 -13.60770;20.48321;-7.32501;,
 -11.81974;15.48918;-7.82792;,
 -11.80472;15.48918;-1.54019;,
 -13.61328;15.48918;-1.52551;,
 -13.60723;15.48918;-7.81326;,
 -13.60770;20.48321;-7.32501;,
 -11.81810;20.48321;-7.33968;,
 -11.81974;18.58301;-7.82792;,
 -13.60723;18.58301;-7.81326;,
 -13.62220;18.58301;7.74694;,
 -11.78258;18.58301;7.73223;,
 -11.78328;20.48321;7.23881;,
 -13.62173;20.48321;7.25352;,
 -13.62220;15.48918;7.74694;,
 -13.61612;15.48918;1.42038;,
 -11.79769;15.48918;1.40569;,
 -11.78258;15.48918;7.73223;,
 -13.62173;20.48321;7.25352;,
 -13.61621;20.48321;1.51528;,
 -13.61612;18.58301;1.42038;,
 -13.62220;18.58301;7.74694;,
 -11.78457;22.06401;5.85811;,
 -11.79513;23.23681;1.43475;,
 -13.61614;23.23681;1.44946;,
 -13.62040;22.06401;5.87283;,
 -11.81974;15.48918;-7.82792;,
 -13.60723;15.48918;-7.81326;,
 -13.61328;15.48918;-1.52551;,
 -13.60723;15.48918;-7.81326;,
 -13.61612;15.48918;1.42038;,
 -13.62220;15.48918;7.74694;,
 -13.62220;15.48918;7.74694;,
 -11.78258;15.48918;7.73223;,
 -13.62040;22.06401;5.87283;,
 -13.61614;23.23681;1.44946;,
 -13.61328;23.23680;-1.52550;,
 -13.60902;22.06401;-5.95022;,
 -11.81280;22.06401;-5.96490;,
 -13.60902;22.06401;-5.95022;,
 -11.78457;22.06401;5.85811;,
 -13.62040;22.06401;5.87283;;
 
 159;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;14,0,3,15;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;23,22,24,25;,
 4;17,26,27,18;,
 4;28,16,19,29;,
 4;30,31,32,33;,
 4;33,32,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;31,40,41,32;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;47,56,57,48;,
 4;58,46,49,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;75,74,92,93;,
 4;70,65,64,71;,
 4;87,86,81,80;,
 4;94,95,77,76;,
 4;70,69,82,81;,
 4;81,86,65,70;,
 4;85,66,65,86;,
 4;90,89,61,60;,
 4;91,90,85,84;,
 4;60,66,85,90;,
 4;67,66,60,63;,
 4;96,73,72,97;,
 4;79,78,98,99;,
 3;92,74,69;,
 3;74,73,69;,
 3;73,62,69;,
 3;62,61,69;,
 3;69,61,82;,
 3;61,89,82;,
 3;82,89,83;,
 3;89,98,83;,
 3;98,78,83;,
 3;78,77,83;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;136,137,138,139;,
 4;140,141,133,132;,
 4;106,105,142,143;,
 4;103,118,117,100;,
 4;144,113,112,145;,
 4;127,126,146,147;,
 4;139,122,121,136;,
 4;148,149,137,136;,
 4;103,102,150,151;,
 4;151,152,118,103;,
 4;119,118,152,153;,
 4;114,109,108,115;,
 4;131,130,125,124;,
 4;154,155,121,120;,
 4;136,121,155,148;,
 4;146,126,113,144;,
 4;114,113,126,125;,
 4;125,130,109,114;,
 4;129,110,109,130;,
 4;134,133,105,104;,
 4;142,105,133,141;,
 4;101,138,137,102;,
 4;150,102,137,149;,
 4;135,134,129,128;,
 4;104,110,129,134;,
 4;111,110,104,107;,
 4;156,117,116,157;,
 4;100,117,156,143;,
 4;142,101,100,143;,
 4;141,138,101,142;,
 4;139,138,141,140;,
 4;158,122,139,140;,
 4;123,122,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;175,174,192,193;,
 4;194,165,164,195;,
 4;187,186,196,197;,
 4;198,199,177,176;,
 4;170,169,182,181;,
 4;196,186,165,194;,
 4;185,166,165,186;,
 4;190,189,161,160;,
 4;200,201,185,184;,
 4;202,166,185,201;,
 4;167,166,202,203;,
 4;204,173,172,205;,
 4;179,178,206,207;,
 3;192,174,169;,
 3;174,173,169;,
 3;173,162,169;,
 3;162,161,169;,
 3;169,161,182;,
 3;161,189,182;,
 3;182,189,183;,
 3;189,206,183;,
 3;206,178,183;,
 3;178,177,183;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;223,222,240,241;,
 4;242,213,212,243;,
 4;235,234,244,245;,
 4;246,247,225,224;,
 4;218,217,230,229;,
 4;244,234,213,242;,
 4;233,214,213,234;,
 4;238,237,209,208;,
 4;248,249,233,232;,
 4;250,214,233,249;,
 4;215,214,250,251;,
 4;252,221,220,253;,
 4;227,226,254,255;,
 3;222,221,240;,
 3;240,221,217;,
 3;221,210,217;,
 3;210,209,217;,
 3;209,237,217;,
 3;217,237,230;,
 3;230,237,231;,
 3;237,254,231;,
 3;254,226,231;,
 3;226,225,231;;
 
 MeshMaterialList {
  1;
  159;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\TreasureChest.jpg";
   }
  }
 }
 MeshNormals {
  166;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.004233;0.849357;-0.527802;,
  0.004324;0.848817;0.528670;,
  0.000000;-1.000000;-0.000000;,
  -0.001039;0.991615;-0.129223;,
  0.008139;0.125419;0.992070;,
  1.000000;-0.000001;0.000963;,
  1.000000;-0.000000;0.000963;,
  -0.007933;0.126682;-0.991912;,
  1.000000;-0.000001;0.000963;,
  0.001055;0.991620;0.129187;,
  -0.007077;0.467077;-0.884188;,
  1.000000;0.000000;0.000962;,
  1.000000;-0.000001;0.000962;,
  1.000000;-0.000002;0.000962;,
  0.007256;0.465011;0.885275;,
  -0.002386;0.853972;-0.520314;,
  0.002390;0.853438;0.521190;,
  -0.002582;0.853970;-0.520316;,
  0.002593;0.853436;0.521191;,
  -0.000627;0.991987;-0.126338;,
  -0.000579;0.991987;-0.126337;,
  -0.002484;0.853971;-0.520315;,
  -0.000603;0.991987;-0.126337;,
  0.002491;0.853437;0.521190;,
  -0.999996;0.000002;0.002916;,
  -0.999996;0.000001;0.002917;,
  -0.999505;0.031422;0.001479;,
  0.004742;0.128287;0.991726;,
  1.000000;0.000000;0.000000;,
  -0.004918;0.129577;-0.991557;,
  -0.004733;0.129577;-0.991558;,
  0.000628;0.991991;0.126304;,
  0.000604;0.991991;0.126303;,
  0.000579;0.991991;0.126303;,
  -0.999874;0.015713;0.002198;,
  -0.004366;0.474850;-0.880056;,
  0.004213;0.472768;0.881177;,
  -0.999901;0.001243;0.014036;,
  -0.999964;0.000622;0.008475;,
  -0.999996;0.000002;0.002917;,
  -0.999996;0.000002;0.002915;,
  -0.004201;0.474852;-0.880056;,
  -0.004233;0.849357;-0.527802;,
  0.004324;0.848817;0.528670;,
  -0.001039;0.991615;-0.129223;,
  0.008139;0.125419;0.992070;,
  1.000000;-0.000000;0.000962;,
  1.000000;-0.000000;0.000963;,
  -0.007933;0.126682;-0.991912;,
  1.000000;-0.000000;0.000963;,
  0.001055;0.991620;0.129187;,
  -0.007077;0.467077;-0.884188;,
  1.000000;0.000000;0.000963;,
  1.000000;0.000001;0.000963;,
  1.000000;0.000001;0.000963;,
  0.007256;0.465011;0.885275;,
  0.004233;0.849357;0.527802;,
  -0.004323;0.848817;-0.528669;,
  0.001039;0.991615;0.129223;,
  -0.008135;0.125418;-0.992071;,
  -1.000000;-0.000000;-0.000962;,
  -1.000000;-0.000000;-0.000963;,
  0.007933;0.126683;0.991911;,
  -1.000000;-0.000000;-0.000963;,
  -0.001055;0.991620;-0.129187;,
  0.007077;0.467077;0.884188;,
  -1.000000;0.000000;-0.000963;,
  -1.000000;0.000001;-0.000963;,
  -1.000000;0.000001;-0.000963;,
  -0.007253;0.465011;-0.885275;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000001;0.000962;,
  1.000000;0.000001;0.000962;,
  0.008207;0.000000;0.999966;,
  1.000000;0.000000;0.000963;,
  1.000000;0.000000;0.000962;,
  1.000000;0.000000;0.000963;,
  1.000000;0.000000;0.000963;,
  -0.007996;-0.000003;-0.999968;,
  1.000000;0.000000;0.000962;,
  1.000000;0.000001;0.000962;,
  1.000000;-0.000001;0.000962;,
  1.000000;-0.000002;0.000961;,
  -0.999997;0.000000;0.002389;,
  -0.999997;-0.000111;0.002443;,
  -0.999997;-0.000326;0.002509;,
  -0.999996;-0.000494;0.002732;,
  -0.999996;-0.000543;0.002635;,
  -0.999997;-0.000320;0.002359;,
  -0.999997;-0.000320;0.002387;,
  -0.999997;-0.000350;0.002424;,
  -0.999998;-0.000168;0.001797;,
  -0.999999;-0.000176;0.001680;,
  -0.999999;0.000029;0.001150;,
  -0.999999;0.000000;0.001439;,
  0.004384;0.472767;0.881176;,
  0.004935;0.128287;0.991725;,
  0.004548;0.128287;0.991727;,
  0.004041;0.472769;0.881177;,
  -0.004036;0.474853;-0.880056;,
  -0.004548;0.129578;-0.991559;,
  -0.999996;0.000000;0.002917;,
  -0.999996;0.000000;0.002917;,
  -0.999886;0.014566;-0.004083;,
  -0.999514;0.029128;-0.011081;,
  0.004586;-0.000002;0.999989;,
  0.004781;-0.000001;0.999989;,
  0.004977;0.000000;0.999988;,
  -0.004960;-0.000004;-0.999988;,
  -0.004773;-0.000004;-0.999989;,
  -0.004586;-0.000004;-0.999989;,
  -0.999842;-0.015615;0.008469;,
  -0.999414;-0.031226;0.014017;,
  -0.999996;0.000000;0.002917;,
  -0.999996;0.000000;0.002915;,
  1.000000;0.000000;0.000962;,
  1.000000;-0.000001;0.000961;,
  0.008207;0.000000;0.999966;,
  1.000000;0.000000;0.000963;,
  1.000000;0.000000;0.000962;,
  1.000000;0.000000;0.000963;,
  1.000000;0.000000;0.000961;,
  -0.007996;-0.000003;-0.999968;,
  1.000000;0.000002;0.000962;,
  1.000000;0.000002;0.000962;,
  1.000000;0.000002;0.000963;,
  1.000000;0.000002;0.000963;,
  -0.999997;0.000000;0.002387;,
  -0.999997;-0.000108;0.002440;,
  -0.999997;-0.000325;0.002508;,
  -0.999996;-0.000493;0.002732;,
  -0.999996;-0.000545;0.002636;,
  -0.999997;-0.000321;0.002359;,
  -0.999997;-0.000321;0.002388;,
  -0.999997;-0.000351;0.002425;,
  -0.999998;-0.000169;0.001794;,
  -0.999999;-0.000177;0.001684;,
  -0.999999;0.000027;0.001146;,
  -0.999999;0.000000;0.001419;,
  -1.000000;-0.000000;-0.000962;,
  -1.000000;-0.000001;-0.000961;,
  -0.008201;0.000000;-0.999966;,
  -1.000000;0.000000;-0.000963;,
  -1.000000;0.000000;-0.000962;,
  -1.000000;0.000000;-0.000963;,
  -1.000000;0.000000;-0.000961;,
  0.007996;0.000000;0.999968;,
  -1.000000;0.000001;-0.000963;,
  -1.000000;0.000001;-0.000963;,
  -1.000000;0.000002;-0.000963;,
  -1.000000;0.000002;-0.000963;,
  0.999994;0.000000;-0.003360;,
  0.999996;-0.000288;-0.002906;,
  0.999996;-0.000047;-0.002874;,
  0.999997;-0.000365;-0.002487;,
  0.999996;-0.000545;-0.002636;,
  0.999997;-0.000320;-0.002346;,
  0.999997;-0.000343;-0.002415;,
  0.999997;-0.000322;-0.002387;,
  0.999998;-0.000169;-0.001794;,
  0.999999;-0.000177;-0.001684;,
  0.999999;0.000027;-0.001147;,
  0.999999;0.000000;-0.001421;;
  159;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;73,73,73,73;,
  4;31,31,31,31;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;73,73,73,73;,
  4;31,31,31,31;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;73,73,73,73;,
  4;31,31,31,31;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;73,73,73,73;,
  4;31,31,31,31;,
  4;12,12,4,4;,
  4;8,11,15,16;,
  4;5,5,5,5;,
  4;17,17,7,7;,
  4;10,10,13,13;,
  4;5,5,5,5;,
  4;74,14,9,75;,
  4;3,6,6,3;,
  4;7,7,76,76;,
  4;77,11,8,78;,
  4;75,9,79,80;,
  4;81,81,10,10;,
  4;5,5,5,5;,
  4;79,9,11,77;,
  4;14,15,11,9;,
  4;6,6,12,12;,
  4;82,83,14,74;,
  4;84,15,14,83;,
  4;16,15,84,85;,
  4;4,17,17,4;,
  4;13,13,3,3;,
  3;86,87,88;,
  3;87,89,88;,
  3;89,90,88;,
  3;90,91,88;,
  3;88,91,92;,
  3;91,93,92;,
  3;92,93,94;,
  3;93,95,94;,
  3;95,96,94;,
  3;96,97,94;,
  4;40,41,37,29;,
  4;34,35,26,21;,
  4;31,31,31,31;,
  4;5,5,5,5;,
  4;98,39,30,99;,
  4;32,33,44,38;,
  4;5,5,5,5;,
  4;31,31,31,31;,
  4;24,25,22,20;,
  4;27,28,42,43;,
  4;18,23,25,24;,
  4;26,35,36,19;,
  4;100,30,39,101;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;102,44,33,103;,
  4;104,105,28,27;,
  4;29,37,106,107;,
  4;108,109,30,100;,
  4;99,30,109,110;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;111,112,33,32;,
  4;103,33,112,113;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;22,25,35,34;,
  4;36,35,25,23;,
  4;41,42,28,37;,
  4;106,37,28,105;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;26,39,98,21;,
  4;101,39,26,19;,
  4;114,41,40,115;,
  4;116,42,41,114;,
  4;43,42,116,117;,
  4;24,44,102,18;,
  4;38,44,24,20;,
  4;53,53,46,46;,
  4;49,52,56,57;,
  4;5,5,5,5;,
  4;58,58,48,48;,
  4;51,51,54,54;,
  4;5,5,5,5;,
  4;118,55,50,119;,
  4;45,47,47,45;,
  4;48,48,120,120;,
  4;121,52,49,122;,
  4;119,50,123,124;,
  4;125,125,51,51;,
  4;5,5,5,5;,
  4;123,50,52,121;,
  4;55,56,52,50;,
  4;47,47,53,53;,
  4;126,127,55,118;,
  4;128,56,55,127;,
  4;57,56,128,129;,
  4;46,58,58,46;,
  4;54,54,45,45;,
  3;130,131,132;,
  3;131,133,132;,
  3;133,134,132;,
  3;134,135,132;,
  3;132,135,136;,
  3;135,137,136;,
  3;136,137,138;,
  3;137,139,138;,
  3;139,140,138;,
  3;140,141,138;,
  4;67,67,60,60;,
  4;63,66,70,71;,
  4;5,5,5,5;,
  4;72,72,62,62;,
  4;65,65,68,68;,
  4;5,5,5,5;,
  4;142,69,64,143;,
  4;59,61,61,59;,
  4;62,62,144,144;,
  4;145,66,63,146;,
  4;143,64,147,148;,
  4;149,149,65,65;,
  4;5,5,5,5;,
  4;147,64,66,145;,
  4;69,70,66,64;,
  4;61,61,67,67;,
  4;150,151,69,142;,
  4;152,70,69,151;,
  4;71,70,152,153;,
  4;60,72,72,60;,
  4;68,68,59,59;,
  3;154,155,156;,
  3;156,155,157;,
  3;155,158,157;,
  3;158,159,157;,
  3;159,160,157;,
  3;157,160,161;,
  3;161,160,162;,
  3;160,163,162;,
  3;163,164,162;,
  3;164,165,162;;
 }
 MeshTextureCoords {
  256;
  0.476587;0.393717;,
  0.523413;0.393717;,
  0.523413;0.346891;,
  0.476587;0.346891;,
  0.523413;0.300066;,
  0.476587;0.300066;,
  0.523413;0.253241;,
  0.476587;0.253241;,
  0.523413;0.206415;,
  0.476587;0.206415;,
  0.017655;0.370933;,
  0.164367;0.370933;,
  0.164367;0.246578;,
  0.017655;0.246578;,
  0.429762;0.393717;,
  0.429762;0.346891;,
  0.451190;0.995139;,
  0.548810;0.995139;,
  0.548810;0.897520;,
  0.451190;0.897520;,
  0.548810;0.799901;,
  0.451190;0.799901;,
  0.548810;0.702282;,
  0.451190;0.702282;,
  0.548810;0.604663;,
  0.451190;0.604663;,
  0.646429;0.995139;,
  0.646429;0.897520;,
  0.353571;0.995139;,
  0.353571;0.897520;,
  0.474471;0.371354;,
  0.525529;0.371354;,
  0.525529;0.320296;,
  0.474471;0.320296;,
  0.525529;0.269238;,
  0.474471;0.269238;,
  0.525529;0.218180;,
  0.474471;0.218180;,
  0.525529;0.167122;,
  0.474471;0.167122;,
  0.576587;0.371354;,
  0.576587;0.320296;,
  0.017090;0.377180;,
  0.166129;0.377180;,
  0.166129;0.241885;,
  0.017090;0.241885;,
  0.461773;0.444169;,
  0.538227;0.444169;,
  0.538227;0.367714;,
  0.461773;0.367714;,
  0.538227;0.291259;,
  0.461773;0.291259;,
  0.538227;0.214804;,
  0.461773;0.214804;,
  0.538227;0.138349;,
  0.461773;0.138349;,
  0.614683;0.444169;,
  0.614683;0.367714;,
  0.385317;0.444169;,
  0.385317;0.367714;,
  0.506593;0.305535;,
  0.506593;0.325914;,
  0.518843;0.325914;,
  0.518843;0.305535;,
  0.518843;0.285558;,
  0.506593;0.285558;,
  0.506593;0.294891;,
  0.518843;0.294891;,
  0.518843;0.247470;,
  0.506593;0.247470;,
  0.506593;0.267849;,
  0.518843;0.267849;,
  0.556529;0.353865;,
  0.536150;0.353865;,
  0.536150;0.363198;,
  0.556529;0.363198;,
  0.443471;0.363198;,
  0.463850;0.363198;,
  0.463850;0.353865;,
  0.443471;0.353865;,
  0.481157;0.267849;,
  0.500349;0.267849;,
  0.500349;0.247470;,
  0.481157;0.247470;,
  0.481157;0.294891;,
  0.500349;0.294891;,
  0.500349;0.285558;,
  0.481157;0.285558;,
  0.481157;0.325914;,
  0.500349;0.325914;,
  0.500349;0.305535;,
  0.481157;0.305535;,
  0.536150;0.380907;,
  0.556529;0.380907;,
  0.443471;0.380907;,
  0.463850;0.380907;,
  0.536150;0.343221;,
  0.556529;0.343221;,
  0.463850;0.343221;,
  0.443471;0.343221;,
  0.625000;0.820609;,
  0.543734;0.820609;,
  0.543734;0.882519;,
  0.625000;0.882519;,
  0.543734;0.500000;,
  0.543734;0.635189;,
  0.625000;0.635189;,
  0.625000;0.500000;,
  0.625000;0.367481;,
  0.543734;0.367481;,
  0.543734;0.429391;,
  0.625000;0.429391;,
  0.625000;0.114811;,
  0.543734;0.114811;,
  0.543734;0.250000;,
  0.625000;0.250000;,
  0.875000;0.820609;,
  0.739811;0.820609;,
  0.739811;0.882519;,
  0.875000;0.882519;,
  0.125000;0.882519;,
  0.260189;0.882519;,
  0.260189;0.820609;,
  0.125000;0.820609;,
  0.375000;0.250000;,
  0.502315;0.250000;,
  0.502315;0.114811;,
  0.375000;0.114811;,
  0.375000;0.429391;,
  0.502315;0.429391;,
  0.502315;0.367481;,
  0.375000;0.367481;,
  0.375000;0.635189;,
  0.502315;0.635189;,
  0.502315;0.500000;,
  0.375000;0.500000;,
  0.375000;0.882519;,
  0.502315;0.882519;,
  0.502315;0.820609;,
  0.375000;0.820609;,
  0.375000;0.750000;,
  0.502315;0.750000;,
  0.543734;0.750000;,
  0.625000;0.750000;,
  0.543734;0.000000;,
  0.625000;0.000000;,
  0.502315;0.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.502315;1.000000;,
  0.543734;1.000000;,
  0.625000;1.000000;,
  0.739811;1.000000;,
  0.875000;1.000000;,
  0.125000;1.000000;,
  0.260189;1.000000;,
  0.739811;0.750000;,
  0.875000;0.750000;,
  0.260189;0.750000;,
  0.125000;0.750000;,
  0.505999;0.314701;,
  0.505999;0.333245;,
  0.517146;0.333245;,
  0.517146;0.314701;,
  0.160165;0.307523;,
  0.112398;0.307523;,
  0.112398;0.335902;,
  0.160165;0.335902;,
  0.517146;0.261864;,
  0.505999;0.261864;,
  0.505999;0.280408;,
  0.517146;0.280408;,
  0.551439;0.358679;,
  0.532895;0.358679;,
  0.532895;0.367171;,
  0.551439;0.367171;,
  0.448561;0.367171;,
  0.467105;0.367171;,
  0.467105;0.358679;,
  0.448561;0.358679;,
  0.482854;0.280408;,
  0.500318;0.280408;,
  0.500318;0.261864;,
  0.482854;0.261864;,
  0.013218;0.335902;,
  0.088052;0.335902;,
  0.088052;0.307523;,
  0.013218;0.307523;,
  0.482854;0.333245;,
  0.500318;0.333245;,
  0.500318;0.314701;,
  0.482854;0.314701;,
  0.532895;0.383286;,
  0.551439;0.383286;,
  0.112398;0.253668;,
  0.160165;0.253668;,
  0.088052;0.253668;,
  0.013218;0.253668;,
  0.448561;0.383286;,
  0.467105;0.383286;,
  0.013218;0.368270;,
  0.088052;0.368270;,
  0.112398;0.368270;,
  0.160165;0.368270;,
  0.532895;0.348994;,
  0.551439;0.348994;,
  0.467105;0.348994;,
  0.448561;0.348994;,
  0.506484;0.329257;,
  0.506484;0.349300;,
  0.518533;0.349300;,
  0.518533;0.329257;,
  0.154797;0.306608;,
  0.110313;0.306608;,
  0.110313;0.340497;,
  0.154797;0.340497;,
  0.518533;0.272148;,
  0.506484;0.272148;,
  0.506484;0.292191;,
  0.518533;0.292191;,
  0.555599;0.376791;,
  0.535555;0.376791;,
  0.535555;0.385970;,
  0.555599;0.385970;,
  0.444401;0.385970;,
  0.464445;0.385970;,
  0.464445;0.376791;,
  0.444401;0.376791;,
  0.481467;0.292191;,
  0.500343;0.292191;,
  0.500343;0.272148;,
  0.481467;0.272148;,
  0.017948;0.340497;,
  0.087640;0.340497;,
  0.087640;0.306608;,
  0.017948;0.306608;,
  0.481467;0.349300;,
  0.500343;0.349300;,
  0.500343;0.329257;,
  0.481467;0.329257;,
  0.535555;0.403388;,
  0.555599;0.403388;,
  0.110313;0.242299;,
  0.154797;0.242299;,
  0.087640;0.242299;,
  0.017948;0.242299;,
  0.444401;0.403388;,
  0.464445;0.403388;,
  0.017948;0.379149;,
  0.087640;0.379149;,
  0.110313;0.379149;,
  0.154797;0.379149;,
  0.535555;0.366322;,
  0.555599;0.366322;,
  0.464445;0.366322;,
  0.444401;0.366322;;
 }
}
