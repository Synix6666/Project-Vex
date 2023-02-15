#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

typedef HRESULT(APIENTRY* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
IDXGISwapChainPresent oIDXGISwapChainPresent;

typedef void(APIENTRY* ID3D11DrawIndexed)(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
ID3D11DrawIndexed oID3D11DrawIndexed;

