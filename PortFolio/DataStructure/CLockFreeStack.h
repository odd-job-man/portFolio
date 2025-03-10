#pragma once
#include <cstdint>
#include <optional>

#define QUEUE
#include "CTlsObjectPool.h"


template<typename T>
class CLockFreeStack
{
private:
	struct Node
	{
		T data_;
		uintptr_t metaNext_;
		Node(T&& data)
			:data_{ std::forward<T>(data)}, metaNext_{0}
		{
		}
	};

public:
	CTlsObjectPool<Node, true> pool_;
	alignas(64) uintptr_t metaTop_;
	alignas(64) size_t metaCnt_;

	alignas(64) long num_;

	CLockFreeStack()
		:metaTop_{ 0 }, metaCnt_{ 0 }
	{
		InterlockedExchange(&num_, 0);
	}

	void Push(T data)
	{
		Node* pNewNode = pool_.Alloc(std::move(data));

		uintptr_t metaTop;
		uintptr_t newMetaTop = CAddressTranslator::GetMetaAddr
		(
			CAddressTranslator::GetCnt(&metaCnt_),
			(uintptr_t)pNewNode
		);

		do
		{
			metaTop = metaTop_;
			pNewNode->metaNext_ = metaTop;
		} while (InterlockedCompareExchange(&metaTop_, newMetaTop, metaTop) != metaTop);

		InterlockedIncrement(&num_);
	}

	std::optional<T> Pop()
	{
		Node* realTop;
		uintptr_t metaTop;
		uintptr_t newMetaTop;
		do
		{
			metaTop = metaTop_;
			if (!metaTop)
			{
				return std::nullopt;
			}
			realTop = (Node*)CAddressTranslator::GetRealAddr(metaTop);
			newMetaTop = realTop->metaNext_;
		} while (InterlockedCompareExchange(&metaTop_, newMetaTop, metaTop) != metaTop);

		T data = std::move(realTop->data_);
		pool_.Free(realTop);
		InterlockedDecrement(&num_);
		return data;
	}


};
#undef QUEUE
