package com.sequarius.lightplayer.fragment;

import java.util.List;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.sequarius.lightplayer.MainActivity;
import com.sequarius.lightplayer.R;
import com.sequarius.lightplayer.database.PlayListDAO;
import com.sequarius.lightplayer.object.Song;
import com.sequarius.lightplayer.service.MusicService;

public class PlayListFragment extends Fragment {
	private ListView mListView;
	private List<Song> songs;
	private MyAdapter adapter;
	private MusicService mMusicService;
	private int mId=1;
	private int songCount=0;

	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		View view = inflater.inflate(R.layout.layout_playlist, null);
		mListView = (ListView) view.findViewById(R.id.ListView_playlist);
		PlayListDAO listDAO = new PlayListDAO(getActivity());
		songs = listDAO.selectAll();
		songCount=songs.size();
		adapter = new MyAdapter();
		mListView.setAdapter(adapter);
		Intent intent = new Intent("com.sequarius.action.musicservice");
		mMainActivity = (MainActivity) getActivity();
		getActivity().bindService(intent, connection, Context.BIND_AUTO_CREATE);
		mListView.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				mId=position;
				mMusicService.changePlaying(songs.get(position).getUri());
				mMainActivity.setLrc(songs.get(position).getName());
				// Toast.makeText(getActivity(),songs.get(position).getName(),
				// Toast.LENGTH_SHORT).show();
				changePlayingTittle(position);
			}


		});
		return view;
	}
	/**
	 * �ı����ڲ��Ž�������ڲ��Ÿ�������Ϣ
	 * @param position ���Ÿ������б�λ��
	 */
	private void changePlayingTittle(int position) {
		String strTemp = songs.get(position).getName();
		// �ָ�����ַ���
		String[] info = strTemp.split("-");
		String strPlayer = info[0];
		String strName = "δ֪����";
		if (info.length > 1 && info[1].endsWith("mp3")) {
			
			strName = info[1].replace(".mp3", "");
			
		}else{
			strName=strTemp;
			strPlayer="";
		}
		mMainActivity.changeInfo(strName, strPlayer);
	}

	@Override
	public void onResume() {
		// TODO Auto-generated method stub
		PlayListDAO listDAO = new PlayListDAO(getActivity());
		songs = listDAO.selectAll();
		// Log.i("mylog", "���ã�");
		adapter.notifyDataSetChanged();
		super.onResume();
	}

	private class MyAdapter extends BaseAdapter {

		@Override
		public int getCount() {
			// TODO Auto-generated method stub
			return songs.size();
		}

		@Override
		public Object getItem(int position) {
			// TODO Auto-generated method stub
			return songs.get(position);
		}

		@Override
		public long getItemId(int position) {
			// TODO Auto-generated method stub
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			// TODO Auto-generated method stub
			Song song = songs.get(position);
			View view = View.inflate(getActivity(), R.layout.layout_item, null);
			TextView tvName = (TextView) view.findViewById(R.id.textview_name);
			TextView tvID = (TextView) view.findViewById(R.id.textview_id);
			TextView tvPlayer = (TextView) view
					.findViewById(R.id.textview_player);
			String strTemp = song.getName();
			// �ָ�����ַ���
			String[] info = strTemp.split("-");
			if (info.length > 1) {
				tvPlayer.setText(info[0]);
				if (info[1].endsWith("mp3")) {
					info[1] = info[1].replace(".mp3", "");
				}
				tvName.setText(info[1]);
			}else{
				tvName.setText(info[0]);
			}
			tvID.setText(song.getId() + "");
			return view;
		}

	}

	private ServiceConnection connection = new ServiceConnection() {

		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method stub
			getActivity().unbindService(connection);
		}

		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			// TODO Auto-generated method stub
			// ����һ��service����
			mMusicService = ((MusicService.MyBinder) service).getService();

		}
	};
	private MainActivity mMainActivity;
	/**
	 * �����б�˳�����һ����������ŵ��б�ĩβ������ת����һ��
	 */
	public void playNextSong(){
		if(mId<songCount-1){
		mId++;
		}else{
			mId=1;
		}
		changePlayingTittle(mId);
		mMusicService.changePlaying(songs.get(mId).getUri());
		mMainActivity.setLrc(songs.get(mId).getName());
	}
	/**
	 * �����б�˳�����һ��������б��￪ͷ�����������һ��
	 */
	public void playPreSong(){
		if(mId>1){
			mId--;
		}else{
			mId=songCount-1;
		}
		changePlayingTittle(mId);
		mMusicService.changePlaying(songs.get(mId).getUri());
		
		mMainActivity.setLrc(songs.get(mId).getName());
	}
	/**
	 * ����Ӧ�ú��ʼ��Service��Դ��
	 */
	public void initService(){
		changePlayingTittle(0);
		mMusicService.changePlaying(songs.get(0).getUri());
		mMainActivity.setLrc(songs.get(0).getName());
	}
}
