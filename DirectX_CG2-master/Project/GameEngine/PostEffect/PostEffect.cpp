/*
* PostEffect.cpp
* ポストエフェクトの処理
*/

#include "PostEffect.h"
#include <d3dx12.h>

using namespace DirectX;

PostEffect::PostEffect() : Sprite()
{

}

void PostEffect::Draw(SpriteCommon* spriteCommon) {
	//テクスチャコマンド
	spriteCommon->SetTextureCommands(textureIndex_);

	//頂点データ
	vertices[LB].pos = { 0.0f,		size_.y,	0.0f };
	vertices[LT].pos = { 0.0f,		0.0f,		0.0f };
	vertices[RB].pos = { size_.x,	size_.y,	0.0f };
	vertices[RT].pos = { size_.x,	0.0f,		0.0f };

	ComPtr<ID3D12Resource> textureBuffer = spriteCommon->GetTextureBuffer(textureIndex_);
	//指定番号の画像が読み込み済みなら
	if (textureBuffer) {
		//テクスチャ情報取得
		D3D12_RESOURCE_DESC resDescPE = textureBuffer->GetDesc();

		float tex_left = textureLeftTop_.x / resDescPE.Width;
		float tex_right = (textureLeftTop_.x + textureSize_.x) / resDescPE.Width;
		float tex_top = textureLeftTop_.y / resDescPE.Height;
		float tex_bottom = (textureLeftTop_.y + textureSize_.y) / resDescPE.Height;
		//頂点のUVに反映する
		vertices[LB].uv = { tex_left, tex_bottom };		//左下
		vertices[LT].uv = { tex_left, tex_top };		//左上
		vertices[RB].uv = { tex_right, tex_bottom };	//右下
		vertices[RT].uv = { tex_right, tex_top };		//右上
	}

	//頂点データをGPUに転送
	std::copy(std::begin(vertices), std::end(vertices), vertMap);

	//色情報をGPUに転送
	constMapMaterial->color = color_;

	//単位行列を代入
	constMapTransform->mat = XMMatrixIdentity();
	//ワールド変換行列
	XMMATRIX matWorld;
	matWorld = XMMatrixIdentity();

	XMMATRIX matRot;
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation_.z));
	matWorld *= matRot;

	XMMATRIX matTrans;
	matTrans = XMMatrixTranslation(position_.x, position_.y, 0.0f);
	matWorld *= matTrans;

	//射影変換行列
	XMMATRIX matProjection = XMMatrixIdentity();
	matProjection.r[3].m128_f32[0] = -1.0f;
	matProjection.r[3].m128_f32[1] = 1.0f;
	matProjection.r[0].m128_f32[0] = 2.0f / WinApp::window_width;
	matProjection.r[1].m128_f32[1] = -2.0f / WinApp::window_height;
	constMapTransform->mat = matWorld * matProjection;

	//パイプラインステートの設定
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetPipelineState(pipelineState.Get());
	//ルートシグネチャの設定
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootSignature(rootSignature.Get());
	//プリミティブ形状を設定
	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//頂点バッファビューの設定コマンド
	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	spriteCommon->GetDirectXCommon()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//定数バッファビュー(CBV)の設定コマンド
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//定数バッファビュー(CBV)の設定コマンド
	spriteCommon->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());

	//描画コマンド
	spriteCommon->GetDirectXCommon()->GetCommandList()->DrawInstanced(_countof(vertices), 1, 0, 0);

}