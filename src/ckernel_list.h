/**
 * Copyright (C) 2024 Fusion-io.  All rights reserved.
 *
 * This header was taken from the Linux kernel
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H
#include <malloc.h>
#include <string.h>



 /**
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */
struct list_head {
	struct list_head* next, * prev;
};

/**
* Description: Place the macro at the first member of the app struct.
* Note: This macro must be placed as the first member of the app struct.
*/
#define LIST_OBJECT_IN_APP(header_name) \
		struct list_head header_name


/**
* Description: The effect is similar to NULL, that is, 
*			   the address is inaccessible in user space.
*/
#define LIST_POISON1  ((void *) 0x00100100)
#define LIST_POISON2  ((void *) 0x00200200)


		/**
		* Description: Initialize the linked list.
		* Way 1：LIST_HEAD(my_class);
		* Way 2：
		*	    struct list_head my_class;
		*	    INIT_LIST_HEAD(&my_class);
		*/
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

#define LIST_HEAD_INIT(name) { &(name), &(name) }


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	static inline void INIT_LIST_HEAD(struct list_head* list)
	{
		list->next = list;
		list->prev = list;
	}

		/**
		 * __list_add:  Insert a pnew entry between two known consecutive entries.
		 * @pnew: a new node that will be added to the linked list.
		 * @prev: the precursor of pnew after the pnew join operation is completed.
		 * @next: the successor of pnew after the pnew join operation is completed.
		 *
		 * Note: This is only for internal list manipulation where we know
		 *		 the prev/next entries already!
		 */
	static inline void __list_add(struct list_head* pnew,
		struct list_head* prev,
		struct list_head* next)
	{
		next->prev = pnew;
		pnew->next = next;
		pnew->prev = prev;
		prev->next = pnew;
	}

	/**
	 * list_add:  Add a pnew entry.
	 * @pnew: pnew entry to be added.
	 * @head: list head to add it after.
	 *
	 * Description: Header insertion (this is a doubly linked list with a head).
	 *				Insert a pnew entry after the specified head.
	 *				This is good for implementing stacks.
	 */
	static inline void list_add(struct list_head* pnew,
		struct list_head* head)
	{
		__list_add(pnew, head, head->next);
	}

	/**
	 * list_add_tail:  Add a pnew entry.
	 * @pnew: pnew entry to be added.
	 * @head: list head to add it before.
	 *
	 * Description: Tail insertion method
	 *				Insert a pnew entry before the specified head.
	 *				This is useful for implementing queues.
	 */
	static inline void list_add_tail(struct list_head* pnew,
		struct list_head* head)
	{
		__list_add(pnew, head->prev, head);
	}

	/*
	 * __list_del:  Delete a list entry by making the prev/next entries
	 * point to each other.
	 * @prev: the precursor of the deleted point.
	 * @next: the successor to the deleted point.
	 *
	 * Note: This is only for internal list manipulation where we know
	 *		 the prev/next entries already!
	 */
	static inline void __list_del(struct list_head* prev,
		struct list_head* next)
	{
		next->prev = prev;
		prev->next = next;
	}

	/**
	 * list_del:  Delete entry from list.
	 * @entry: the element to delete from the list.
	 *
	 * Description: only responsible for the removal from the linked list, 
	 *				and is not responsible for the memory processing of the node.
	 * Note: list_empty on entry does not return true after this, the entry is
	 *		 in an undefined state.
	 */
	static inline void list_del(struct list_head* entry)
	{
		__list_del(entry->prev, entry->next);
		entry->next = (struct list_head*)LIST_POISON1;
		entry->prev = (struct list_head*)LIST_POISON2;
	}

	/**
	 * list_del_init:  Delete entry from list and reinitialize it.
	 * @entry: the element to delete from the list.
	 *
	 * Description: remove the 'entry' node from a linked list,
	 *				and initialize the entry as an orphan node that its predecessor and successor are its own.
	 */
	static inline void list_del_init(struct list_head* entry)
	{
		__list_del(entry->prev, entry->next);
		INIT_LIST_HEAD(entry);
	}

	/**
	 * list_move:  Delete from one list and add as another's head.
	 * @list: the entry to move.
	 * @head: the head that will precede our entry.
	 *
	 * Description: Delete the 'list' node from a linked list and head insert it into the 'head' linked list.
	 */
	static inline void list_move(struct list_head* list,
		struct list_head* head)
	{
		__list_del(list->prev, list->next);
		list_add(list, head);
	}

	/**
	 * list_move_tail:  Delete from one list and add as another's tail.
	 * @list: the entry to move.
	 * @head: the head that will follow our entry.
	 *
	 * Description: Delete the 'list' node from a linked list and tail insert it into the 'head' linked list.
	 */
	static inline void list_move_tail(struct list_head* list,
		struct list_head* head)
	{
		__list_del(list->prev, list->next);
		list_add_tail(list, head);
	}

	/**
	 * list_replace:  Replace old entry by pnew one.
	 * @old : the element to be replaced.
	 * @pnew : the pnew element to insert.
	 *
	 * Description: Use 'pnew' instead of 'old'.
	 * Note: if 'old' was empty, it will be overwritten.
	 */
	static inline void list_replace(struct list_head* old,
		struct list_head* pnew)
	{
		pnew->next = old->next;
		pnew->next->prev = pnew;
		pnew->prev = old->prev;
		pnew->prev->next = pnew;
	}

	/**
	 * list_replace_init:  replace old entry by pnew one,and init the old entry.
	 * @old : the element to be replaced.
	 * @pnew : the pnew element to insert.
	 *
	 * Description: Use 'pnew' instead of 'old', and initialize 'old' as an orphaned node.
	 */
	static inline void list_replace_init(struct list_head* old,
		struct list_head* pnew)
	{
		list_replace(old, pnew);
		INIT_LIST_HEAD(old);
	}

	/**
	 * list_is_last:  tests whether @list is the last entry in list @head.
	 * @list: the entry to test.
	 * @head: the head of the list.
	 *
	 * Description: Check whether the node 'list' is the last node in the linked list 'head'.
	 */
	static inline int list_is_last(const struct list_head* list,
		const struct list_head* head)
	{
		return list->next == head;
	}

	/**
	 * list_empty:  tests whether a list is empty
	 * @head: the list to test.
	 *
	 * Description: Check whether the linked list 'head' is an empty linked list (with only one marker header node).
	 */
	static inline int list_empty(const struct list_head* head)
	{
		return head->next == head;
	}

	/**
	 * list_empty_careful:  tests whether a list is empty and not being modified
	 * @head: the list to test
	 *
	 * Description:
	 * tests whether a list is empty _and_ checks that no other CPU might be
	 * in the process of modifying either member (next or prev)
	 *
	 * Note: using list_empty_careful() without synchronization
	 * can only be safe if the only activity that can happen
	 * to the list entry is list_del_init(). Eg. it cannot be used
	 * if another CPU could re-list_add() it.
	 */
	static inline int list_empty_careful(const struct list_head* head)
	{
		struct list_head* next = head->next;
		return (next == head) && (next == head->prev);
	}

	/**
	 * __list_splice:  join two lists
	 * @list: the pnew list to add.
	 * @head: the place to add it in the first list.
	 *
	 * Description: Merge the linked list 'list' into the linked list 'head', 
	 *				which is in the form of a header insertion, and does not contain the marker header node of the 'list'.
	 * Note: The actual implementation function that implements the merge operation of the linked list internally.
	 */
	static inline void __list_splice(struct list_head* list,
		struct list_head* head)
	{
		struct list_head* first = list->next;
		struct list_head* last = list->prev;
		struct list_head* at = head->next;

		first->prev = head;
		head->next = first;

		last->next = at;
		at->prev = last;
	}

	/**
	 * list_splice:  join two lists
	 * @list: the pnew list to add.
	 * @head: the place to add it in the first list.
	 *
	 * Description: Merge the linked list 'list' into the linked list 'head', 
	 *				which is in the form of a header insertion, and does not contain the marker header node of the 'list'.
	 */
	static inline void list_splice(struct list_head* list, struct list_head* head)
	{
		if (!list_empty(list))
			__list_splice(list, head);
	}

	/**
	 * list_splice_init:  join two lists and reinitialise the emptied list.
	 * @list: the pnew list to add.
	 * @head: the place to add it in the first list.
	 *
	 * Description: The list at @list is reinitialised
	 */
	static inline void list_splice_init(struct list_head* list,
		struct list_head* head)
	{
		if (!list_empty(list)) {
			__list_splice(list, head);
			INIT_LIST_HEAD(list);
		}
	}

#ifdef __cplusplus
}
#endif // __cplusplus


	 /**
	  * list_for_each:	iterate over a list
	  * @pos:	the &struct list_head to use as a loop cursor.
	  * @type:	the type of the app struct.
	  * @head:	the head for your list.
	  */
#define list_for_each(pos, type, head) \
	for (pos = (type*)((head)->next);  \
			&pos->member !=  (head); \
        	pos = (type*)(pos->member.next))

	  /**
	   * __list_for_each:	iterate over a list
	   * @pos:		the &struct list_head to use as a loop cursor.
	   * @type:		the type of the app struct.
	   * @head:		the head for your list.
	   *
	   * this variant differs from list_for_each() in that it's the
	   * simplest possible list iteration code, no prefetching is done.
	   * use this for code that knows the list to be very short (empty
	   * or 1 entry) most of the time.
	   */
#define __list_for_each(pos, type, head) \
	for (pos = (type*)((head)->next);  \
			&pos->member !=  (head); \
			pos = (type*)(pos->member.next))

	   /**
		* list_for_each_prev:	iterate over a list backwards
		* @pos:		the &struct list_head to use as a loop cursor.
		* @type:	the type of the app struct.
		* @head:	the head for your list.
		*/
#define list_for_each_prev(pos, type, head) \
	for (pos = (type*)((head)->prev);  \
			&pos->member !=  (head);  \
        	pos = (type*)(pos->member.prev))

		/**
		 * list_for_each_safe:  iterate over a list safe against removal of list entry
		 * @pos:	the &struct list_head to use as a loop cursor.
		 * @n:		another &struct list_head to use as temporary storage.
		 * @type:	the type of the app struct.
		 * @head:	the head for your list.
		 */
#define list_for_each_safe(pos, n, type, head) \
	for (pos = (type*)((head)->next),   \
			n = (type*)(pos->next);  \
			&pos->member != (head);  \
			pos = n, n = (type*)(pos->member.next))

		 /**
		  * list_for_each_entry:	iterate over list of given type
		  * @pos:	the type * to use as a loop cursor.
		  * @type:	the type of the app struct.
		  * @head:	the head for your list.
		  * @member:the name of the list_struct within the struct.
		  *
		  * Note: don't use to iterate over list when it's some one element will be removal.
		  */
#define list_for_each_entry(pos, type, head, member)		\
	for (pos = (type*)((head)->next);	\
			 &pos->member != (head); 	\
			 pos = (type*)(pos->member.next))

		  /**
		   * list_for_each_entry_reverse: iterate backwards over list of given type.
		   * @pos:	the type * to use as a loop cursor.
		   * @type:	the type of the app struct.
		   * @head:	the head for your list.
		   * @member:the name of the list_struct within the struct.
		   *
		   * Note: don't use to iterate over list when it's some one element will be removal.
		   */
#define list_for_each_entry_reverse(pos, type, head, member)			\
	for (pos = (type*)((head)->prev);	\
			 &pos->member != (head); 	\
			 pos = (type*)(pos->member.prev))

		   /**
			* list_for_each_entry_safe: iterate over list of given type safe against removal of list entry.
			* @pos:	the type * to use as a loop cursor.
			* @n:	another type * to use as temporary storage
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*/
#define list_for_each_entry_safe(pos, n, type, head, member)		 \
	for (pos = (type*)((head)->next),	\
			n = (type*)(pos->member.next);	\
			&pos->member != (head); 	\
			pos = n, n = (type*)(n->member.next))

			/**
			* list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue.
			* @pos:	the type * to use as a start point
			* @type:the type of the app struct.
			* @head:the head of the list
			* @member:the name of the list_struct within the struct.
			*
			* prepares a pos entry for use as a start point in list_for_each_entry_continue.
			*/
#define list_prepare_entry(pos, type, head, member) \
	((pos) ? (&pos->member) : (type*)(head))

			/**
			* list_for_each_entry_continue - continue iteration over list of given type.
			* @pos:	the type * to use as a loop cursor.
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*
			* continue to iterate over list of given type, continuing after
			* the current position.
			*/
#define list_for_each_entry_continue(pos, type, head, member) 		\
	for (pos = (type*)(pos->member.next);	\
			&pos->member != (head);	\
			pos = (type*)(pos->member.next))

			/**
			* list_for_each_entry_from - iterate over list of given type from the current point.
			* @pos:	the type * to use as a loop cursor.
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*
			* iterate over list of given type, continuing from current position.
			*/
#define list_for_each_entry_from(pos, type, head, member) 			\
	for (; &pos->member != (head);	\
 			pos = (type*)(pos->member.next))

			/**
			* list_for_each_entry_safe_continue.
			* @pos:	the type * to use as a loop cursor.
			* @n:	another type * to use as temporary storage.
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*
			* iterate over list of given type, continuing after current point,
			* safe against removal of list entry.
			*/
#define list_for_each_entry_safe_continue(pos, n, type, head, member) 		\
	for (pos = (type*)(pos->member.next), 		\
 			n = (type*)(pos->member.next);		\
 			&pos->member != (head);		\
 			pos = n, n = (type*)(n->member.next))

			/**
			* list_for_each_entry_safe_from.
			* @pos:	the type * to use as a loop cursor.
			* @n:	another type * to use as temporary storage.
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*
			* iterate over list of given type from current point, safe against
			* removal of list entry.
			*/
#define list_for_each_entry_safe_from(pos, n, type, head, member) 			\
	for (n = (type*)(pos->member.next);		\
 			&pos->member != (head);		\
 			pos = n, n = (type*)(n->member.next))

			/**
			* list_for_each_entry_safe_reverse.
			* @pos:	the type * to use as a loop cursor.
			* @n:	another type * to use as temporary storage.
			* @type:the type of the app struct.
			* @head:the head for your list.
			* @member:the name of the list_struct within the struct.
			*
			* iterate backwards over list of given type, safe against removal
			* of list entry.
			*/
#define list_for_each_entry_safe_reverse(pos, n, type, head, member)		\
	for (pos = (type*)((head)->prev),	\
			n = (type*)(pos->member.prev);	\
 			&pos->member != (head); 	\
 			pos = n, n = (type*)(n->member.prev))



#endif // !_LINUX_LIST_H