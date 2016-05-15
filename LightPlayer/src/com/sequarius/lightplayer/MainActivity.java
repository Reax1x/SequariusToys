package com.sequarius.lightplayer;

import java.util.ArrayList;
import java.util.List;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.view.PagerTabStrip;
import android.support.v4.view.ViewPager;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import com.sequarius.lightplayer.fragment.LyricFragment;
import com.sequarius.lightplayer.fragment.PlayListFragment;
import com.sequarius.lightplayer.fragment.PlayingFragment;

public class MainActivity extends FragmentActivity {

	private ViewPager mViewPager;
	private LyricFragment mLyricFragment;
	private PlayingFragment mPlayingFragment;
	private PlayListFragment mPlayListFragment;
	// ��ǩ�б�
	private List<Fragment> mfragmentList;
	// �����б�
	private List<String> mTitleList;
	// �������Ե����ö���
	private PagerTabStrip mPagerTabStrip;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		initActivityLayout();

	}

	private void initActivityLayout() {
		mViewPager = (ViewPager) findViewById(R.id.viewPager);
		mViewPager.setOffscreenPageLimit(5);//viewpager����󻺴���
		mPagerTabStrip = (PagerTabStrip) findViewById(R.id.pagetittle);
		// ��ʼ��Fragment
		mPagerTabStrip.setBackgroundColor(0xFF333333);
		mPagerTabStrip.setTabIndicatorColor(Color.WHITE);
		mPagerTabStrip.setTextColor(Color.WHITE);
		mLyricFragment = new LyricFragment();
		mPlayingFragment = new PlayingFragment();
		mPlayListFragment = new PlayListFragment();

		// ��ʼ��List
		mfragmentList = new ArrayList<Fragment>();
		mTitleList = new ArrayList<String>();

		mfragmentList.add(mPlayingFragment);
		mfragmentList.add(mPlayListFragment);
		mfragmentList.add(mLyricFragment);

		mTitleList.add("���ڲ���");
		mTitleList.add("�����б�");
		mTitleList.add("���");
		FragmentManager manager = getSupportFragmentManager();
		mViewPager.setAdapter(new MyViewPagerAdapter(manager, mfragmentList,
				mTitleList));
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// TODO Auto-generated method stub
		MenuInflater inflater = getMenuInflater();
		inflater.inflate(R.menu.menu_main, menu);
		return true;

	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case R.id.meue_action_add:
			Intent intent = new Intent(MainActivity.this,
					SearchMusicActivity.class);
			startActivity(intent);
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	/**
	 * �ı����ڲ��Ž���ĸ���ժҪ��������fragmentͨ��activity����
	 * 
	 * @param name
	 *            ������
	 * @param player
	 *            ������
	 */
	public void changeInfo(String name, String player) {
		mPlayingFragment.changeInfo(name, player);
	}

	/*
	 * ������һ����������fragmentͨ��activity����
	 */
	public void playNext() {
		mPlayListFragment.playNextSong();
	}

	/*
	 * ������һ����������fragmentͨ��activity����
	 */
	public void playPre() {
		mPlayListFragment.playPreSong();
	}
	/**
	 * ��ʼ�����ŷ���,������fragement����
	 */
	public void InitServiceRes() {
		mPlayListFragment.initService();
	}
	/**
	 * �������λ��
	 * @param position ��ǰ�����ڵ�position
	 */
	public void lrcScroll(int position){
		mLyricFragment.changeLrcPostion(position);
	}
	public int[] getTimeShaft(){
		return mLyricFragment.getTimerShaft();
	}
	public void setLrc(String songName){
		String strLrcPath=songName.replace("mp3", "lrc");
		mLyricFragment.setLrc(strLrcPath);
	}
}
