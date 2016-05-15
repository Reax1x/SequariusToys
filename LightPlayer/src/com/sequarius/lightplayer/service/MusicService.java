package com.sequarius.lightplayer.service;

import java.io.IOException;

import com.sequarius.lightplayer.R;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.os.Binder;
import android.os.IBinder;
import android.test.suitebuilder.annotation.MediumTest;
import android.util.Log;

/**
 * ��̨���ֲ��ŷ���ȷ��activity�ڷǻ״̬����������������
 * 
 * @author Sequarius
 *
 */
public class MusicService extends Service {
	// ���������ֵ
	public static int MAX_PROGRESS = 0;
	// ��ǰ����ֵ
	private int progress = 0;
	// ���ȵĻص��ӿ�
	private OnProgressListener mOnProgressListener;

	/**
	 * ע��ص������������ⲿ����
	 * 
	 * @param onProgressListener
	 */
	public void setOnProgressListner(OnProgressListener onProgressListener) {
		mOnProgressListener = onProgressListener;
	}

	/**
	 * ���ڸ�Activity���õĻ�ȡ���ȵķ���
	 * 
	 * @return ��ǰ���Ž���
	 */
	public int getProgress() {
		return progress;
	}

	/**
	 * ��������service�е�����
	 */
	public void continuePlay() {
		if (mMediaPlayer != null && (!mMediaPlayer.isPlaying())) {
			mMediaPlayer.start();
		}
	}

	/**
	 * ��ͣ����service������
	 */
	public void pausePlay() {
		if (mMediaPlayer != null && mMediaPlayer.isPlaying()) {
			mMediaPlayer.pause();
			Log.i("mylog", currentTime() + "---------" + totalTime());
		}
	}

	public void Playing() {
		mMediaPlayer.start();
	}

	public boolean isNull() {
		return mMediaPlayer == null ? true : false;
	}

	/**
	 * �л������в��ŵĸ���
	 * 
	 * @param uri
	 *            �����ľ���·��
	 */
	public void changePlaying(String uri) {
		try {
			if (mMediaPlayer == null) {
				mMediaPlayer = new MediaPlayer();
			}
			mMediaPlayer.pause();
			mMediaPlayer.reset();// �ͷ�֮ǰ��Դ
			mMediaPlayer.setDataSource(uri);
			mMediaPlayer.prepare();
		} catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalStateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		mMediaPlayer.start();
	}

	private MediaPlayer mMediaPlayer;

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		seekBarCallBack();
		super.onCreate();
		// mMediaPlayer = MediaPlayer.create(this, R.raw.test);
	}

	public boolean isPlaying() {
		return mMediaPlayer.isPlaying();
	}

	public class MyBinder extends Binder {
		/**
		 * ��ȡ��ǰService��ʵ��
		 * 
		 * @return
		 */
		public MusicService getService() {
			return MusicService.this;
		}
	}

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return new MyBinder();
	}

	private String totalTime() {
		int time = mMediaPlayer.getDuration();
		return timeToString(time);
	}

	private String currentTime() {
		int time = mMediaPlayer.getCurrentPosition();
		return timeToString(time);
	}

	private String timeToString(int time) {
		time /= 1000;
		int minutes = time / 60;
		int seconds = time % 60;
		return seconds < 10 ? (minutes + ":0" + seconds)
				: (minutes + ":" + seconds);

	}

	public void setProgress(int positon) {
		mMediaPlayer.seekTo(positon);
		progress = positon;
	}

	/**
	 * playing����seekbar����
	 */
	private void seekBarCallBack() {
		new Thread(new Runnable() {
			@Override
			public void run() {
				while (true) {

					// ���ȷ����仯֪ͨ���÷�
					if (mOnProgressListener != null && mMediaPlayer != null) {
						MAX_PROGRESS = mMediaPlayer.getDuration();
						progress = mMediaPlayer.getCurrentPosition();
						mOnProgressListener.onProgress(progress, MAX_PROGRESS);
					}

					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}

				}
			}
		}).start();
	}

}
