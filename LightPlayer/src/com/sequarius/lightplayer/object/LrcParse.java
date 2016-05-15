package com.sequarius.lightplayer.object;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
/**
 * ��������LRC���͸�ʵĽ���
 * @author Sequarius
 *
 */
public class LrcParse {
	private TreeMap<Integer, String> treeMap;

	public LrcParse(File file) throws IOException, FileNotFoundException {
		super();
		InputStreamReader isr = new InputStreamReader(new FileInputStream(file), "UTF-8");
        BufferedReader bufferedReader = new BufferedReader(isr);
        List<String> lines=new ArrayList<String>();
        String line;
        while ((line=bufferedReader.readLine())!=null) {
            lines.add(line);
        }
        treeMap=new TreeMap<>();
        for (Iterator<String> iterator = lines.iterator(); iterator.hasNext();) {
            String string = (String) iterator.next();
            parserLine(string);
        }
        bufferedReader.close();
	}
	/**
	 * ���ڷ��ؽ�����ĸ��
	 * @return ����ʱ��˳�������Map����
	 */
	public TreeMap<Integer, String> getLrc(){
		return treeMap;
	}
	/**
	 * ��String�͵��ַ���������ʱ��
	 * @param timeStr ʱ����ַ��� ��ʽΪ[xx:xx.xx]
	 * @return ת����ĺ���intʱ��ֵ
	 */
	private int strToInt(String timeStr){  
		//ȥ��[]
    	String reg="[\\[|\\]]";
    	//��������λ���ַ���
		timeStr=timeStr.replaceAll(reg, "");
        String[] strPre = timeStr.split(":");
        int min = Integer.parseInt(strPre[0]);  
        //������ͺ���λ���ַ���
        int sec=0;  
        int mill=0;  
        if(strPre[1].contains(".")){  
            String[] strNext=strPre[1].split("\\.");  
//            System.out.println(s[1]);
            sec =Integer.parseInt(strNext[0]);  
            mill=Integer.parseInt(strNext[1]);  
        }else{  
            sec=Integer.parseInt(strPre[1]);  
        }  
        return min*60*1000+sec*1000+mill*10;  
    }  
	/**
	 * ����ÿһ�еĸ�ʲ�����Map
	 */
    private void parserLine(String line){
		String reg ="\\[(\\d{1,2}:\\d{1,2}\\.\\d{1,2})\\]|\\[(\\d{1,2}:\\d{1,2})\\]"; 
        Pattern pattern = Pattern.compile(reg);  
        Matcher matcher=pattern.matcher(line);
        List<Integer> times=new ArrayList<Integer>();
        while(matcher.find()){
        	int time=strToInt(matcher.group());
        	times.add(time);
        }
        String strLrc=line.replaceAll(reg, "");
        for (Iterator iterator = times.iterator(); iterator.hasNext();) {
			Integer integer = (Integer) iterator.next();
			treeMap.put(integer, strLrc);
		}
        
    }
}