package com.sequarius.lightplayer.fragment;

import java.util.Arrays;
import java.util.List;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

import com.sequarius.lightplayer.MainActivity;
import com.sequarius.lightplayer.R;
import com.sequarius.lightplayer.service.MusicService;
import com.sequarius.lightplayer.service.OnProgressListener;

public class PlayingFragment extends Fragment {
	private MusicService mMusicService;
	private SeekBar mSeekBar;
	private TextView tvName;
	private TextView tvPlayer;
	private CheckBox checkBox;
	private int mMaxProgress;
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		View view=inflater.inflate(R.layout.layout_playing, null);
		view.findViewById(R.id.seekBar1);
		tvName=(TextView)view.findViewById(R.id.textView1);
		tvPlayer=(TextView)view.findViewById(R.id.textView2);
		checkBox=(CheckBox)view.findViewById(R.id.checkbox_playstatus);
		mSeekBar=(SeekBar)view.findViewById(R.id.seekBar1);
		mSeekBar.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				mMusicService.Playing();
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				mMusicService.pausePlay();
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				MainActivity activity=(MainActivity)getActivity();
				int[] timeShaft=activity.getTimeShaft();
				int time=Arrays.binarySearch(timeShaft, progress);				
				activity.lrcScroll(Math.abs(time)-1);
//				Log.i("mylog", "�ص������ڳ�����"+time);
				if (fromUser) {
					// TODO Auto-generated method stub
					mMusicService.setProgress(progress);
				}
				if(mMaxProgress-progress<1000){
					activity.playNext();
				}
			}
		});
		checkBox.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
				// TODO Auto-generated method stub
				//�ж��Ƿ���δ򿪲���������ʱ��ʼ��service��Դ
				initServiceRes();
				if(isChecked){
					
					mMusicService.continuePlay();
				}else{
					mMusicService.pausePlay();
				}
				
			}
		});
		Button button_next=(Button)view.findViewById(R.id.button_next);
		button_next.setOnClickListener(new OnClickListener() {
			
			MainActivity mainActivity=(MainActivity)getActivity();
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				mainActivity.playNext();
			}
		});
		Button button_pre=(Button)view.findViewById(R.id.button_pre);
		button_pre.setOnClickListener(new OnClickListener() {
			
			MainActivity mainActivity=(MainActivity)getActivity();
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				mainActivity.playPre();
			}
		});
		
		Intent intent=new Intent("com.sequarius.action.musicservice");
		getActivity().bindService(intent, connection, Context.BIND_AUTO_CREATE);
		return view;
		
	}
	/**
	 * ��service
	 */
	private ServiceConnection connection=new ServiceConnection() {
		
		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method stub
			getActivity().unbindService(connection);
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			// TODO Auto-generated method stub
			//����һ��service����
			mMusicService=((MusicService.MyBinder)service).getService();
			//ע��ص��ӿڽ��ܲ��Ž��ȱ仯
			mMusicService.setOnProgressListner(new OnProgressListener() {
				
				@Override
				public void onProgress(int progress,int max) {
					// TODO Auto-generated method stub
					mSeekBar.setMax(max);
					mSeekBar.setProgress(progress);
					mMaxProgress=max;
				}
			});
		}
	};
	/**
	 * �ı�ui�����ڲ�����Ϣ
	 * @param name ������	
	 * @param player ������
	 */
	public void changeInfo(String name,String player){
		Log.i("mylog", name+"-------"+player);

		tvName.setText(name);
		tvPlayer.setText(player);
		checkBox.setChecked(true);
		
	}
	/**
	 * ��ʼ��service����Դͬʱ��ʼ��playing����
	 */
	private void initServiceRes(){
		boolean result=tvName.getText().equals("δ֪����")&&(tvPlayer.getText().equals("δ֪����"))&&(mMusicService.isNull());
		if(result){
			MainActivity activity=(MainActivity)getActivity();
			activity.InitServiceRes();
		}
	}
}
