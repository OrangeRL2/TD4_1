/*
* Sprite.cpp
* スプライト一枚ごとの処理
*/

#include "Sprite.h"
#include "DirectXTex.h"
#include <string>

void Sprite::Initialize(SpriteCommon* spriteCommon, uint32_t textureIndex) {

	scale = { 1.0f,1.0f,1.0f };
	rotation_ = { 0.0f,0.0f,0.0f };
	position_ = { 0.0f,0.0f };
	spriteCommon_ = spriteCommon;
	//ヒープ設定
	D3D12_HEAP_PROPERTIES cbHeapProp{};
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPUへの転送用
	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataMaterial) + 0xff) & ~0xff;	//256バイアラインメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = spriteCommon_->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&cbHeapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffMaterial));
	assert(SUCCEEDED(result));

	//定数バッファのマッピング

	result = constBuffMaterial->Map(0, nullptr, (void**)&constMapMaterial);//マッピング
	assert(SUCCEEDED(result));

	constMapMaterial->color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	{

		//ヒープ設定
		D3D12_HEAP_PROPERTIES cbHeapProp2{};
		cbHeapProp2.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPUへの転送用
		//リソース設定
		D3D12_RESOURCE_DESC cbResourceDesc2{};
		cbResourceDesc2.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		cbResourceDesc2.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0xff;	//256バイアラインメント
		cbResourceDesc2.Height = 1;
		cbResourceDesc2.DepthOrArraySize = 1;
		cbResourceDesc2.MipLevels = 1;
		cbResourceDesc2.SampleDesc.Count = 1;
		cbResourceDesc2.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

		//定数バッファの生成
		/*定数バッファ・・・全ピクセル共通のデータを送るときに利用するバッファ*/
		//ComPtr<ID3D12Resource> constBuffMaterial;

		result = spriteCommon_->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
			&cbHeapProp2,//ヒープ設定
			D3D12_HEAP_FLAG_NONE,
			&cbResourceDesc2,//リソース設定
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&constBuffTransform));
		assert(SUCCEEDED(result));

		//定数バッファのマッピング
		result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);//マッピング
		assert(SUCCEEDED(result));

	}

	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPUへの転送用

	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeVB;//頂点データ全体のサイズ
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//頂点バッファの生成
	result = spriteCommon_->GetDirectXCommon()->GetDevice()->CreateCommittedResource(
		&heapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	//GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	/*仮想メモリ・・・ハードディスクの一部をメモリとして利用する際に、ハードディスク上に作成されるファイル*/
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));
	//全頂点に対して
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];	//座標をコピー
	}

	//繋がりを解除
	vertBuff->Unmap(0, nullptr);

	//頂点バッファビューの生成
	/*GPUに頂点バッファの場所を教えるためのもの*/
	//GPU仮想アドレス
	/*仮想アドレス・・・コンピュータ内のメモリ領域に対して、メモリ装置内での物理的な配置とは独立に割り当てられた所在情報（アドレス）のこと*/
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	//頂点一つ分のデータサイズ
	vbView.StrideInBytes = sizeof(vertices[0]);

	//テクスチャサイズをイメージに合わせる
	if (textureIndex != UINT32_MAX) {
		textureIndex_ = textureIndex;
		AdjustTextrueSize();
		//テクスチャサイズをスプライトのサイズに適用
		size_ = textureSize_;
	}
}

void Sprite::Update() {

}

void Sprite::Draw() {
	//テクスチャコマンド
	spriteCommon_->SetTextureCommands(textureIndex_);

	float left = (0.0f - anchorpoint_.x) * size_.x;
	float right = (1.0f - anchorpoint_.x) * size_.x;
	float top = (0.0f - anchorpoint_.y) * size_.y;
	float bottom = (1.0f - anchorpoint_.y) * size_.y;

	//頂点データ
	vertices[LB].pos = { left,	bottom,	0.0f };
	vertices[LT].pos = { left,	top,	0.0f };
	vertices[RB].pos = { right,	bottom,	0.0f };
	vertices[RT].pos = { right,	top,	0.0f };

	ComPtr<ID3D12Resource> textureBuffer = spriteCommon_->GetTextureBuffer(textureIndex_);
	//指定番号の画像が読み込み済みなら
	if (textureBuffer) {
		//テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

		float tex_left = textureLeftTop_.x / resDesc.Width;
		float tex_right = (textureLeftTop_.x + textureSize_.x) / resDesc.Width;
		float tex_top = textureLeftTop_.y / resDesc.Height;
		float tex_bottom = (textureLeftTop_.y + textureSize_.y) / resDesc.Height;
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

	//頂点バッファビューの設定コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vbView);

	spriteCommon_->GetDirectXCommon()->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//定数バッファビュー(CBV)の設定コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, constBuffMaterial->GetGPUVirtualAddress());

	//定数バッファビュー(CBV)の設定コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());

	//描画コマンド
	spriteCommon_->GetDirectXCommon()->GetCommandList()->DrawInstanced(_countof(vertices), 1, 0, 0);

}

void Sprite::AdjustTextrueSize() {
	ComPtr<ID3D12Resource> textureBuffer = spriteCommon_->GetTextureBuffer(textureIndex_);
	assert(textureBuffer);

	//テクスチャ情報取得
	D3D12_RESOURCE_DESC resDesc = textureBuffer->GetDesc();

	textureSize_.x = static_cast<float>(resDesc.Width);
	textureSize_.y = static_cast<float>(resDesc.Height);
}