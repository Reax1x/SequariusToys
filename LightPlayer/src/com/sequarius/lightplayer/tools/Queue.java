package com.sequarius.lightplayer.tools;

import java.util.LinkedList;
/**
 * ���еĹ�����
 * @author Sequarius
 *
 * @param <E>
 */
public class Queue<E> {
	private LinkedList<E> link;

	/**
	 * �ṩ�˹�����ж���Ĺ�������
	 */
	public Queue() {
		link = new LinkedList<E>();
	}

	/**
	 * ���Ԫ�صķ�����
	 */
	public void myAdd(E obj) {
		link.addFirst(obj);
	}

	/**
	 * ��ȡ�ķ�����
	 */
	public E myGet() {
		return link.removeLast();
	}

	/**
	 * �ж϶����Ƿ���Ԫ�ء�
	 */
	public boolean isNull() {
		return link.isEmpty();
	}
}
