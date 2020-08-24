#include "ut_List.h"

#define GET_NODE(PTR_LIST,PTR_NODE) ((Node *)((int)(PTR_NODE)+(PTR_LIST)->short_0xa))
#define GET_NODE_1(PTR_LIST,PTR_NODE) (Node *)((int)(PTR_NODE)+(PTR_LIST)->short_0xa)

namespace nw4r
{
	namespace ut
	{
		static inline Node * List_GetNode(List * list, void * node)
		{
			return (Node *)((int)node + list->offset);
		}
		
		inline void SetFirstObject(List * list, void * node)
		{
			Node * pNode = List_GetNode(list, node);
			
			pNode->next = 0;
			pNode->prev = 0;
		}
		
		static inline void SetObject(List * list, void * node)
		{
			Node * pNode = List_GetNode(list, node);
			
			pNode->prev = list->last;
			pNode->next = 0;
		}
		
		void List_Init(List * list, unsigned short offset)
		{
			list->offset = offset;
			list->first = 0;
			list->last = 0;
			list->size = 0;
		}
		
		void List_Append(List * list, void * node)
		{
			
			if (!list->first)
			{
				SetFirstObject(list, node);
				list->first = node;
				list->last = node;
				list->size++;
			}
			else
			{
				SetObject(list, node);
				List_GetNode(list, list->last)->next = node;
				list->last = node;
				list->size++;
			}
		}
		/*
		UNKTYPE List_Insert(List *, void *, void *)
		{
			
		}
		
		UNKTYPE List_Remove(List *, void *)
		{
			
		}
		
		UNKTYPE List_GetNext(const List *, const void *)
		{
			
		}
		
		UNKTYPE List_GetPrev(const List *, const void *)
		{
			
		}
		
		UNKTYPE List_GetNth(const List *, unsigned short)
		{
			
		}*/
	}
}