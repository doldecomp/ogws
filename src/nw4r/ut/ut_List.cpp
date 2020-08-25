#include "ut_list.h"

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
			
			pNode->next = NULL;
			pNode->prev = NULL;
			list->first = node;
			list->last = node;
			list->size++;
		}
		
		void List_Init(List * list, unsigned short offset)
		{
			list->offset = offset;
			list->first = NULL;
			list->last = NULL;
			list->size = NULL;
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
				pNode->next = NULL;
				
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
				
				pNode->prev = NULL;
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
		
		void List_Remove(List *list, void *node)
        {
            Node * pNode = List_GetNode(list, node);
            if (!pNode->prev)
            {
                list->first = List_GetNode(list, node)->next;
            }
            else
            {
                List_GetNode(list, pNode->prev)->next = pNode->next;
            }

            if (!pNode->next)
            {
                list->last = pNode->prev;
            }
            else
            {
                List_GetNode(list, pNode->next)->prev = pNode->prev;
            }

            pNode->prev = NULL;
            pNode->next = NULL;
            list->size--;
        }
		
        void* List_GetNext(const List *list, const void *node)
		{
			if (node == NULL)
            {
                return list->first;
            }

            return List_GetConstNode(list, node)->next;
		}

        void* List_GetPrev(const List *list, const void *node)
        {
            if (node == NULL)
            {
                return list->last;
            }

            return List_GetConstNode(list, node)->prev;
        }
		
		
		void * List_GetNth(const List * list, unsigned short n)
		{
			void * node;
			int i;
			
			for (i = 0, node = NULL; node = List_GetNext(list, node); i++)
			{
				if (n == i) return node;
			}
			
			return NULL;
		}
	}
}