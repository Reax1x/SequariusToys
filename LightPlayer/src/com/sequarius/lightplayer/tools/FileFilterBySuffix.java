package com.sequarius.lightplayer.tools;

import java.io.File;
import java.io.FileFilter;
/**
 * �ļ����˽ӿڣ�ʵ�ֶ���Ƶ��׺�ļ����ж�
 * @author Sequarius
 *
 */
public class FileFilterBySuffix implements FileFilter {

	private String suffix;
	
	public FileFilterBySuffix(String suffix) {
		super();
		this.suffix = suffix;
	}

	@Override
	public boolean accept(File pathname) {
		
		return pathname.getName().endsWith(suffix);
	}
}
