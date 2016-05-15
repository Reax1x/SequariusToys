package com.sequarius.lightplayer;

import java.io.File;
import java.io.FileFilter;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

import com.sequarius.lightplayer.database.PlayListDAO;
import com.sequarius.lightplayer.tools.FileFilterBySuffix;
import com.sequarius.lightplayer.tools.Queue;

public class SearchMusicActivity extends Activity {
	PlayListDAO mPlayListDAO;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		mPlayListDAO = new PlayListDAO(this);
		setContentView(R.layout.layout_search_music);
		Button button = (Button) findViewById(R.id.button_search_music);
		button.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				int count = searchMusicFile();
				Toast.makeText(SearchMusicActivity.this,
						"ɨ�����,���ҵ�" + count + "�������ļ���", Toast.LENGTH_SHORT)
						.show();
				finish();
			}
		});
	}

	/**
	 * ����SD������MP3�ļ�
	 * 
	 * @return �ҵ���MP3����
	 */

	public int searchMusicFile() {

		// ɨ��Ŀ¼
		File dir = new File("sdcard/");
		// ������
		FileFilter filter = new FileFilterBySuffix("mp3");
		// �������Ҫ����ļ�
		List<File> list = new ArrayList<File>();
		// getFileList(dir, filter, list);

		Queue<File> queue = new Queue<File>();
		File[] files = dir.listFiles();
		for (File file : files) {
			if (file.isDirectory()) {
				queue.myAdd(file);
			} else {
				if (filter.accept(file)) {
					list.add(file);
				}
			}

		}
		while (!queue.isNull()) {
			File subDir = queue.myGet();
			File[] subFiles = subDir.listFiles();
			if (subFiles != null) {
				for (File file : subFiles) {
					if (file.isDirectory()) {
						queue.myAdd(file);
					} else {
						if (filter.accept(file)) {
							list.add(file);
						}
					}

				}
			}
		}
		mPlayListDAO.clear();
		for (File file : list) {
			mPlayListDAO.add(file.getName(), file.getAbsolutePath());
		}
		return list.size();
	}

	// �Զ��з�ʽ�ݹ�
	/*
	 * public void getFileList(File dir, FileFilter filter, List<File> list) {
	 * // TODO Auto-generated method stub File[] files = dir.listFiles(); for
	 * (File file : files) { if (file.isDirectory()) { getFileList(file, filter,
	 * list); } else { if (filter.accept(file)) { list.add(file); } } } }
	 */

}
