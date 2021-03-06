#include "main.fx"

float4x4 g_mWorld : World;          // World matrix
float4x4 g_mWorldView;
//-----------------------------------------------------------------------------
// Vertex Shader: HDRVertLight
// Desc: Process vertex for light objects
//-----------------------------------------------------------------------------
void HDRVertLight( float4 iPos : POSITION,
                   out float4 oPos : POSITION,
                   out float4 Diffuse : TEXCOORD1 )
{
	float4x4 mWorldView = mul(g_mWorld,g_mView);
  // Transform position to screen space
  oPos = mul( iPos, mWorldView );
  oPos = mul( oPos, g_mProj );
  // Diffuse color is the light intensity value
  Diffuse = float4(1,1,1,1);//g_vLightIntensity;
}
//-----------------------------------------------------------------------------
// Pixel Shader: HDRPixLight
// Desc: Process pixel for HDR-enabled scene
//-----------------------------------------------------------------------------
float4 HDRPixLight( float4 Diffuse : TEXCOORD1 ) : COLOR
{
  // Diffuse has the full intensity of the light.
  // Just output it.
  return Diffuse;
}
//-----------------------------------------------------------------------------
// Technique: RenderLight
// Desc: Renders light objects
//-----------------------------------------------------------------------------
technique RenderLight
{
  pass p0
  {
      VertexShader = compile vs_2_0 HDRVertLight();
      PixelShader = compile ps_2_0 HDRPixLight();
  }
}
