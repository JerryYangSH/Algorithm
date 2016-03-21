﻿

// 一致性Hash作为常用的hash算法在分布式系统中经常使用，比普通的余数Hash算法更具伸缩性，在动态添加节点的情况下不会导致大量服务器cache失效。基本原理是将节点取hash映射到hash环，为使得均匀分布可以采用虚拟节点，然后对每次请求计算得到hash值，在hash环中顺时针方向找到下一个相邻的节点。 具体细节可以google，下面给出一致性hash的java代码实现。





package consistentHash;

import java.util.LinkedList;
import java.util.SortedMap;
import java.util.TreeMap;

public class consistentHashWithVirtualNodes {
	public static int VIRTUAL_SERVER_NODE_NUMBER = 5;
	
	public static LinkedList<String> realServers = new LinkedList<String>();
	private static SortedMap virtualNodeMap = new TreeMap<Integer, String>();
	
	private static void buildMap(String[] servers){
		// insert nodes into sortedMap
		for(int i = 0; i < servers.length; i++){
			String virtualServer = servers[i] + "&VS" + String.valueOf(i % VIRTUAL_SERVER_NODE_NUMBER); // map to virtual server
			
			int hash = getHash(virtualServer);
			System.out.println("[" + virtualServer + "] is added in set, its hash value is " + hash);
			virtualNodeMap.put(hash, virtualServer);
		}
	}
	 /**
	  * 使用FNV1_32_HASH算法计算服务器的Hash值,这里不使用重写hashCode的方法，最终效果没区别
	  */
	private static int getHash(String str){
		final int p = 16777619;
		int hash = (int)2166136261L;
		for (int i = 0; i < str.length(); i++)
		     hash = (hash ^ str.charAt(i)) * p;
		hash += hash ;
		hash ^= hash >> 7;
		hash += hash ;
		hash ^= hash >> 17;
		hash += hash ;
		
		if (hash < 0){
			hash = Math.abs(hash);
		}
		return hash;
	}
	
	private static String getServer(String node){
		int hash = getHash(node);
		
		// get the map with values >= such hash
		SortedMap subMap = virtualNodeMap.tailMap(hash);
		Integer k = (Integer) subMap.firstKey();
		
		String virtualNodeName = (String) subMap.get(k);
		return virtualNodeName.substring(0, virtualNodeName.indexOf('&'));
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String[] servers = {"192.168.0.0:111", 
							"192.168.0.1:111", 
							"192.168.0.2:111",
							"192.168.0.3:111", 
							"192.168.0.4:111"};
		buildMap(servers);
		System.out.println();
		
		String[] nodes = {"127.0.0.1:1111",
						  "221.226.0.1:2222",
						  "10.211.0.1:3333",
						  "10.10.32.19:1234",
						  "10.37.127.252:56789",
						  "10.21.0.199:6660"};
		
		
		
		for (int i = 0; i < nodes.length; i++){
			System.out.println("["+nodes[i]+"] hash value is : " +
								getHash(nodes[i]) + " routed to server [" + getServer(nodes[i]) + "]");
		}

	}

}



