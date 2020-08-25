#include "ut_List.h"

namespace nw4r
{
	namespace ut
	{
		static inline Node * List_GetNode(List * list, void * node)
		{
			return (Node *)((int)node + list->offset);
		}
		
		static inline const Node * List_GetConstNode(const List * list, const void * node)
		{
			return (Node *)((int)node + list->offset);
		}
		
		inline void SetFirstObject(List * list, void * node)
		{
			Node * pNode = List_GetNode(list, node);
			
			pNode->next = 0;
			pNode->prev = 0;
			list->first = node;
			list->last = node;
			list->size++;
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
			}
			else
			{
				Node * pNode = List_GetNode(list, node);
				
				pNode->prev = list->last;
				pNode->next = 0;
				
				List_GetNode(list, list->last)->next = node;
				list->last = node;
				list->size++;
			}
		}
		
		inline void List_Prepend(List * list, void * node)
		{
			if (!list->first)
			{
				SetFirstObject(list, node);
			}
			else
			{
				Node * pNode = List_GetNode(list, node);
				
				pNode->prev = 0;
				pNode->next = list->first;
				
				List_GetNode(list, list->first)->prev = node;
				list->first = node;
				list->size++;
			}
		}
		
		void List_Insert(List * list, void * pos, void * node)
		{
			if (!pos)
			{
				List_Append(list, node);
			}
			else if (pos == list->first)
			{
				List_Prepend(list, node);
			}
			else
			{
				Node * pPos = List_GetNode(list, pos);
				Node * pNode = List_GetNode(list, node);
				Node * r6 = List_GetNode(list, pPos->prev);
				pNode->prev = pPos->prev;
				
				pNode->next = pos;
				r6->next = node;
				
				List_GetNode(list, pos)->prev = node;
				list->size++;
			}
		}
		/*
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