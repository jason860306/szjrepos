



<!DOCTYPE html>
<html>
<head>
 <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" >
 <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" >
 
 <meta name="ROBOTS" content="NOARCHIVE">
 
 <link rel="icon" type="image/vnd.microsoft.icon" href="http://www.gstatic.com/codesite/ph/images/phosting.ico">
 
 
 <script type="text/javascript">
 
 
 
 
 var codesite_token = null;
 
 
 var CS_env = {"profileUrl":null,"token":null,"assetHostPath":"http://www.gstatic.com/codesite/ph","domainName":null,"assetVersionPath":"http://www.gstatic.com/codesite/ph/17790938420062995905","projectHomeUrl":"/p/googletest","relativeBaseUrl":"","projectName":"googletest","loggedInUserEmail":null};
 var _gaq = _gaq || [];
 _gaq.push(
 ['siteTracker._setAccount', 'UA-18071-1'],
 ['siteTracker._trackPageview']);
 
 _gaq.push(
 ['projectTracker._setAccount', 'UA-4068653-1'],
 ['projectTracker._trackPageview']);
 
 (function() {
 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
 (document.getElementsByTagName('head')[0] || document.getElementsByTagName('body')[0]).appendChild(ga);
 })();
 
 </script>
 
 
 <title>sample3-inl.h - 
 googletest -
 
 
 Google C++ Testing Framework - Google Project Hosting
 </title>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/17790938420062995905/css/core.css">
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/17790938420062995905/css/ph_detail.css" >
 
 
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/17790938420062995905/css/d_sb.css" >
 
 
 
<!--[if IE]>
 <link type="text/css" rel="stylesheet" href="http://www.gstatic.com/codesite/ph/17790938420062995905/css/d_ie.css" >
<![endif]-->
 <style type="text/css">
 .menuIcon.off { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -42px }
 .menuIcon.on { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 -28px }
 .menuIcon.down { background: no-repeat url(http://www.gstatic.com/codesite/ph/images/dropdown_sprite.gif) 0 0; }
 
 
 
  tr.inline_comment {
 background: #fff;
 vertical-align: top;
 }
 div.draft, div.published {
 padding: .3em;
 border: 1px solid #999; 
 margin-bottom: .1em;
 font-family: arial, sans-serif;
 max-width: 60em;
 }
 div.draft {
 background: #ffa;
 } 
 div.published {
 background: #e5ecf9;
 }
 div.published .body, div.draft .body {
 padding: .5em .1em .1em .1em;
 max-width: 60em;
 white-space: pre-wrap;
 white-space: -moz-pre-wrap;
 white-space: -pre-wrap;
 white-space: -o-pre-wrap;
 word-wrap: break-word;
 font-size: 1em;
 }
 div.draft .actions {
 margin-left: 1em;
 font-size: 90%;
 }
 div.draft form {
 padding: .5em .5em .5em 0;
 }
 div.draft textarea, div.published textarea {
 width: 95%;
 height: 10em;
 font-family: arial, sans-serif;
 margin-bottom: .5em;
 }

 
 .nocursor, .nocursor td, .cursor_hidden, .cursor_hidden td {
 background-color: white;
 height: 2px;
 }
 .cursor, .cursor td {
 background-color: darkblue;
 height: 2px;
 display: '';
 }
 
 
.list {
 border: 1px solid white;
 border-bottom: 0;
}

 
 </style>
</head>
<body class="t4">
<script type="text/javascript">
 window.___gcfg = {lang: 'en'};
 (function() 
 {var po = document.createElement("script");
 po.type = "text/javascript"; po.async = true;po.src = "https://apis.google.com/js/plusone.js";
 var s = document.getElementsByTagName("script")[0];
 s.parentNode.insertBefore(po, s);
 })();
</script>
<div class="headbg">

 <div id="gaia">
 

 <span>
 
 
 <a href="#" id="projects-dropdown" onclick="return false;"><u>My favorites</u> <small>&#9660;</small></a>
 | <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogletest%2Fsource%2Fbrowse%2Ftrunk%2Fsamples%2Fsample3-inl.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogletest%2Fsource%2Fbrowse%2Ftrunk%2Fsamples%2Fsample3-inl.h" onclick="_CS_click('/gb/ph/signin');"><u>Sign in</u></a>
 
 </span>

 </div>

 <div class="gbh" style="left: 0pt;"></div>
 <div class="gbh" style="right: 0pt;"></div>
 
 
 <div style="height: 1px"></div>
<!--[if lte IE 7]>
<div style="text-align:center;">
Your version of Internet Explorer is not supported. Try a browser that
contributes to open source, such as <a href="http://www.firefox.com">Firefox</a>,
<a href="http://www.google.com/chrome">Google Chrome</a>, or
<a href="http://code.google.com/chrome/chromeframe/">Google Chrome Frame</a>.
</div>
<![endif]-->



 <table style="padding:0px; margin: 0px 0px 10px 0px; width:100%" cellpadding="0" cellspacing="0"
 itemscope itemtype="http://schema.org/CreativeWork">
 <tr style="height: 58px;">
 
 
 
 <td id="plogo">
 <link itemprop="url" href="/p/googletest">
 <a href="/p/googletest/">
 
 <img src="http://www.gstatic.com/codesite/ph/images/search-48.gif" alt="Logo" itemprop="image">
 
 </a>
 </td>
 
 <td style="padding-left: 0.5em">
 
 <div id="pname">
 <a href="/p/googletest/"><span itemprop="name">googletest</span></a>
 </div>
 
 <div id="psum">
 <a id="project_summary_link"
 href="/p/googletest/"><span itemprop="description">Google C++ Testing Framework</span></a>
 
 </div>
 
 
 </td>
 <td style="white-space:nowrap;text-align:right; vertical-align:bottom;">
 
 <form action="/hosting/search">
 <input size="30" name="q" value="" type="text">
 
 <input type="submit" name="projectsearch" value="Search projects" >
 </form>
 
 </tr>
 </table>

</div>

 
<div id="mt" class="gtb"> 
 <a href="/p/googletest/" class="tab ">Project&nbsp;Home</a>
 
 
 
 
 <a href="/p/googletest/downloads/list" class="tab ">Downloads</a>
 
 
 
 
 
 <a href="/p/googletest/w/list" class="tab ">Wiki</a>
 
 
 
 
 
 <a href="/p/googletest/issues/list"
 class="tab ">Issues</a>
 
 
 
 
 
 <a href="/p/googletest/source/checkout"
 class="tab active">Source</a>
 
 
 
 
 
 
 
 <div class=gtbc></div>
</div>
<table cellspacing="0" cellpadding="0" width="100%" align="center" border="0" class="st">
 <tr>
 
 
 
 
 
 
 
 <td class="subt">
 <div class="st2">
 <div class="isf">
 
 


 <span class="inst1"><a href="/p/googletest/source/checkout">Checkout</a></span> &nbsp;
 <span class="inst2"><a href="/p/googletest/source/browse/">Browse</a></span> &nbsp;
 <span class="inst3"><a href="/p/googletest/source/list">Changes</a></span> &nbsp;
 
 &nbsp;
 
 
 <form action="/p/googletest/source/search" method="get" style="display:inline"
 onsubmit="document.getElementById('codesearchq').value = document.getElementById('origq').value">
 <input type="hidden" name="q" id="codesearchq" value="">
 <input type="text" maxlength="2048" size="38" id="origq" name="origq" value="" title="Google Code Search" style="font-size:92%">&nbsp;<input type="submit" value="Search Trunk" name="btnG" style="font-size:92%">
 
 
 
 
 
 
 </form>
 <script type="text/javascript">
 
 function codesearchQuery(form) {
 var query = document.getElementById('q').value;
 if (query) { form.action += '%20' + query; }
 }
 </script>
 </div>
</div>

 </td>
 
 
 
 <td align="right" valign="top" class="bevel-right"></td>
 </tr>
</table>


<script type="text/javascript">
 var cancelBubble = false;
 function _go(url) { document.location = url; }
</script>
<div id="maincol"
 
>

 




<div class="expand">
<div id="colcontrol">
<style type="text/css">
 #file_flipper { white-space: nowrap; padding-right: 2em; }
 #file_flipper.hidden { display: none; }
 #file_flipper .pagelink { color: #0000CC; text-decoration: underline; }
 #file_flipper #visiblefiles { padding-left: 0.5em; padding-right: 0.5em; }
</style>
<table id="nav_and_rev" class="list"
 cellpadding="0" cellspacing="0" width="100%">
 <tr>
 
 <td nowrap="nowrap" class="src_crumbs src_nav" width="33%">
 <strong class="src_nav">Source path:&nbsp;</strong>
 <span id="crumb_root">
 
 <a href="/p/googletest/source/browse/">svn</a>/&nbsp;</span>
 <span id="crumb_links" class="ifClosed"><a href="/p/googletest/source/browse/trunk/">trunk</a><span class="sp">/&nbsp;</span><a href="/p/googletest/source/browse/trunk/samples/">samples</a><span class="sp">/&nbsp;</span>sample3-inl.h</span>
 
 


 </td>
 
 
 <td nowrap="nowrap" width="33%" align="right">
 <table cellpadding="0" cellspacing="0" style="font-size: 100%"><tr>
 
 
 <td class="flipper">
 <ul class="leftside">
 
 <li><a href="/p/googletest/source/browse/trunk/samples/sample3-inl.h?r=383" title="Previous">&lsaquo;r383</a></li>
 
 </ul>
 </td>
 
 <td class="flipper"><b>r627</b></td>
 
 </tr></table>
 </td> 
 </tr>
</table>

<div class="fc">
 
 
 
<style type="text/css">
.undermouse span {
 background-image: url(http://www.gstatic.com/codesite/ph/images/comments.gif); }
</style>
<table class="opened" id="review_comment_area"
><tr>
<td id="nums">
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
<pre><table width="100%" id="nums_table_0"><tr id="gr_svn627_1"

><td id="1"><a href="#1">1</a></td></tr
><tr id="gr_svn627_2"

><td id="2"><a href="#2">2</a></td></tr
><tr id="gr_svn627_3"

><td id="3"><a href="#3">3</a></td></tr
><tr id="gr_svn627_4"

><td id="4"><a href="#4">4</a></td></tr
><tr id="gr_svn627_5"

><td id="5"><a href="#5">5</a></td></tr
><tr id="gr_svn627_6"

><td id="6"><a href="#6">6</a></td></tr
><tr id="gr_svn627_7"

><td id="7"><a href="#7">7</a></td></tr
><tr id="gr_svn627_8"

><td id="8"><a href="#8">8</a></td></tr
><tr id="gr_svn627_9"

><td id="9"><a href="#9">9</a></td></tr
><tr id="gr_svn627_10"

><td id="10"><a href="#10">10</a></td></tr
><tr id="gr_svn627_11"

><td id="11"><a href="#11">11</a></td></tr
><tr id="gr_svn627_12"

><td id="12"><a href="#12">12</a></td></tr
><tr id="gr_svn627_13"

><td id="13"><a href="#13">13</a></td></tr
><tr id="gr_svn627_14"

><td id="14"><a href="#14">14</a></td></tr
><tr id="gr_svn627_15"

><td id="15"><a href="#15">15</a></td></tr
><tr id="gr_svn627_16"

><td id="16"><a href="#16">16</a></td></tr
><tr id="gr_svn627_17"

><td id="17"><a href="#17">17</a></td></tr
><tr id="gr_svn627_18"

><td id="18"><a href="#18">18</a></td></tr
><tr id="gr_svn627_19"

><td id="19"><a href="#19">19</a></td></tr
><tr id="gr_svn627_20"

><td id="20"><a href="#20">20</a></td></tr
><tr id="gr_svn627_21"

><td id="21"><a href="#21">21</a></td></tr
><tr id="gr_svn627_22"

><td id="22"><a href="#22">22</a></td></tr
><tr id="gr_svn627_23"

><td id="23"><a href="#23">23</a></td></tr
><tr id="gr_svn627_24"

><td id="24"><a href="#24">24</a></td></tr
><tr id="gr_svn627_25"

><td id="25"><a href="#25">25</a></td></tr
><tr id="gr_svn627_26"

><td id="26"><a href="#26">26</a></td></tr
><tr id="gr_svn627_27"

><td id="27"><a href="#27">27</a></td></tr
><tr id="gr_svn627_28"

><td id="28"><a href="#28">28</a></td></tr
><tr id="gr_svn627_29"

><td id="29"><a href="#29">29</a></td></tr
><tr id="gr_svn627_30"

><td id="30"><a href="#30">30</a></td></tr
><tr id="gr_svn627_31"

><td id="31"><a href="#31">31</a></td></tr
><tr id="gr_svn627_32"

><td id="32"><a href="#32">32</a></td></tr
><tr id="gr_svn627_33"

><td id="33"><a href="#33">33</a></td></tr
><tr id="gr_svn627_34"

><td id="34"><a href="#34">34</a></td></tr
><tr id="gr_svn627_35"

><td id="35"><a href="#35">35</a></td></tr
><tr id="gr_svn627_36"

><td id="36"><a href="#36">36</a></td></tr
><tr id="gr_svn627_37"

><td id="37"><a href="#37">37</a></td></tr
><tr id="gr_svn627_38"

><td id="38"><a href="#38">38</a></td></tr
><tr id="gr_svn627_39"

><td id="39"><a href="#39">39</a></td></tr
><tr id="gr_svn627_40"

><td id="40"><a href="#40">40</a></td></tr
><tr id="gr_svn627_41"

><td id="41"><a href="#41">41</a></td></tr
><tr id="gr_svn627_42"

><td id="42"><a href="#42">42</a></td></tr
><tr id="gr_svn627_43"

><td id="43"><a href="#43">43</a></td></tr
><tr id="gr_svn627_44"

><td id="44"><a href="#44">44</a></td></tr
><tr id="gr_svn627_45"

><td id="45"><a href="#45">45</a></td></tr
><tr id="gr_svn627_46"

><td id="46"><a href="#46">46</a></td></tr
><tr id="gr_svn627_47"

><td id="47"><a href="#47">47</a></td></tr
><tr id="gr_svn627_48"

><td id="48"><a href="#48">48</a></td></tr
><tr id="gr_svn627_49"

><td id="49"><a href="#49">49</a></td></tr
><tr id="gr_svn627_50"

><td id="50"><a href="#50">50</a></td></tr
><tr id="gr_svn627_51"

><td id="51"><a href="#51">51</a></td></tr
><tr id="gr_svn627_52"

><td id="52"><a href="#52">52</a></td></tr
><tr id="gr_svn627_53"

><td id="53"><a href="#53">53</a></td></tr
><tr id="gr_svn627_54"

><td id="54"><a href="#54">54</a></td></tr
><tr id="gr_svn627_55"

><td id="55"><a href="#55">55</a></td></tr
><tr id="gr_svn627_56"

><td id="56"><a href="#56">56</a></td></tr
><tr id="gr_svn627_57"

><td id="57"><a href="#57">57</a></td></tr
><tr id="gr_svn627_58"

><td id="58"><a href="#58">58</a></td></tr
><tr id="gr_svn627_59"

><td id="59"><a href="#59">59</a></td></tr
><tr id="gr_svn627_60"

><td id="60"><a href="#60">60</a></td></tr
><tr id="gr_svn627_61"

><td id="61"><a href="#61">61</a></td></tr
><tr id="gr_svn627_62"

><td id="62"><a href="#62">62</a></td></tr
><tr id="gr_svn627_63"

><td id="63"><a href="#63">63</a></td></tr
><tr id="gr_svn627_64"

><td id="64"><a href="#64">64</a></td></tr
><tr id="gr_svn627_65"

><td id="65"><a href="#65">65</a></td></tr
><tr id="gr_svn627_66"

><td id="66"><a href="#66">66</a></td></tr
><tr id="gr_svn627_67"

><td id="67"><a href="#67">67</a></td></tr
><tr id="gr_svn627_68"

><td id="68"><a href="#68">68</a></td></tr
><tr id="gr_svn627_69"

><td id="69"><a href="#69">69</a></td></tr
><tr id="gr_svn627_70"

><td id="70"><a href="#70">70</a></td></tr
><tr id="gr_svn627_71"

><td id="71"><a href="#71">71</a></td></tr
><tr id="gr_svn627_72"

><td id="72"><a href="#72">72</a></td></tr
><tr id="gr_svn627_73"

><td id="73"><a href="#73">73</a></td></tr
><tr id="gr_svn627_74"

><td id="74"><a href="#74">74</a></td></tr
><tr id="gr_svn627_75"

><td id="75"><a href="#75">75</a></td></tr
><tr id="gr_svn627_76"

><td id="76"><a href="#76">76</a></td></tr
><tr id="gr_svn627_77"

><td id="77"><a href="#77">77</a></td></tr
><tr id="gr_svn627_78"

><td id="78"><a href="#78">78</a></td></tr
><tr id="gr_svn627_79"

><td id="79"><a href="#79">79</a></td></tr
><tr id="gr_svn627_80"

><td id="80"><a href="#80">80</a></td></tr
><tr id="gr_svn627_81"

><td id="81"><a href="#81">81</a></td></tr
><tr id="gr_svn627_82"

><td id="82"><a href="#82">82</a></td></tr
><tr id="gr_svn627_83"

><td id="83"><a href="#83">83</a></td></tr
><tr id="gr_svn627_84"

><td id="84"><a href="#84">84</a></td></tr
><tr id="gr_svn627_85"

><td id="85"><a href="#85">85</a></td></tr
><tr id="gr_svn627_86"

><td id="86"><a href="#86">86</a></td></tr
><tr id="gr_svn627_87"

><td id="87"><a href="#87">87</a></td></tr
><tr id="gr_svn627_88"

><td id="88"><a href="#88">88</a></td></tr
><tr id="gr_svn627_89"

><td id="89"><a href="#89">89</a></td></tr
><tr id="gr_svn627_90"

><td id="90"><a href="#90">90</a></td></tr
><tr id="gr_svn627_91"

><td id="91"><a href="#91">91</a></td></tr
><tr id="gr_svn627_92"

><td id="92"><a href="#92">92</a></td></tr
><tr id="gr_svn627_93"

><td id="93"><a href="#93">93</a></td></tr
><tr id="gr_svn627_94"

><td id="94"><a href="#94">94</a></td></tr
><tr id="gr_svn627_95"

><td id="95"><a href="#95">95</a></td></tr
><tr id="gr_svn627_96"

><td id="96"><a href="#96">96</a></td></tr
><tr id="gr_svn627_97"

><td id="97"><a href="#97">97</a></td></tr
><tr id="gr_svn627_98"

><td id="98"><a href="#98">98</a></td></tr
><tr id="gr_svn627_99"

><td id="99"><a href="#99">99</a></td></tr
><tr id="gr_svn627_100"

><td id="100"><a href="#100">100</a></td></tr
><tr id="gr_svn627_101"

><td id="101"><a href="#101">101</a></td></tr
><tr id="gr_svn627_102"

><td id="102"><a href="#102">102</a></td></tr
><tr id="gr_svn627_103"

><td id="103"><a href="#103">103</a></td></tr
><tr id="gr_svn627_104"

><td id="104"><a href="#104">104</a></td></tr
><tr id="gr_svn627_105"

><td id="105"><a href="#105">105</a></td></tr
><tr id="gr_svn627_106"

><td id="106"><a href="#106">106</a></td></tr
><tr id="gr_svn627_107"

><td id="107"><a href="#107">107</a></td></tr
><tr id="gr_svn627_108"

><td id="108"><a href="#108">108</a></td></tr
><tr id="gr_svn627_109"

><td id="109"><a href="#109">109</a></td></tr
><tr id="gr_svn627_110"

><td id="110"><a href="#110">110</a></td></tr
><tr id="gr_svn627_111"

><td id="111"><a href="#111">111</a></td></tr
><tr id="gr_svn627_112"

><td id="112"><a href="#112">112</a></td></tr
><tr id="gr_svn627_113"

><td id="113"><a href="#113">113</a></td></tr
><tr id="gr_svn627_114"

><td id="114"><a href="#114">114</a></td></tr
><tr id="gr_svn627_115"

><td id="115"><a href="#115">115</a></td></tr
><tr id="gr_svn627_116"

><td id="116"><a href="#116">116</a></td></tr
><tr id="gr_svn627_117"

><td id="117"><a href="#117">117</a></td></tr
><tr id="gr_svn627_118"

><td id="118"><a href="#118">118</a></td></tr
><tr id="gr_svn627_119"

><td id="119"><a href="#119">119</a></td></tr
><tr id="gr_svn627_120"

><td id="120"><a href="#120">120</a></td></tr
><tr id="gr_svn627_121"

><td id="121"><a href="#121">121</a></td></tr
><tr id="gr_svn627_122"

><td id="122"><a href="#122">122</a></td></tr
><tr id="gr_svn627_123"

><td id="123"><a href="#123">123</a></td></tr
><tr id="gr_svn627_124"

><td id="124"><a href="#124">124</a></td></tr
><tr id="gr_svn627_125"

><td id="125"><a href="#125">125</a></td></tr
><tr id="gr_svn627_126"

><td id="126"><a href="#126">126</a></td></tr
><tr id="gr_svn627_127"

><td id="127"><a href="#127">127</a></td></tr
><tr id="gr_svn627_128"

><td id="128"><a href="#128">128</a></td></tr
><tr id="gr_svn627_129"

><td id="129"><a href="#129">129</a></td></tr
><tr id="gr_svn627_130"

><td id="130"><a href="#130">130</a></td></tr
><tr id="gr_svn627_131"

><td id="131"><a href="#131">131</a></td></tr
><tr id="gr_svn627_132"

><td id="132"><a href="#132">132</a></td></tr
><tr id="gr_svn627_133"

><td id="133"><a href="#133">133</a></td></tr
><tr id="gr_svn627_134"

><td id="134"><a href="#134">134</a></td></tr
><tr id="gr_svn627_135"

><td id="135"><a href="#135">135</a></td></tr
><tr id="gr_svn627_136"

><td id="136"><a href="#136">136</a></td></tr
><tr id="gr_svn627_137"

><td id="137"><a href="#137">137</a></td></tr
><tr id="gr_svn627_138"

><td id="138"><a href="#138">138</a></td></tr
><tr id="gr_svn627_139"

><td id="139"><a href="#139">139</a></td></tr
><tr id="gr_svn627_140"

><td id="140"><a href="#140">140</a></td></tr
><tr id="gr_svn627_141"

><td id="141"><a href="#141">141</a></td></tr
><tr id="gr_svn627_142"

><td id="142"><a href="#142">142</a></td></tr
><tr id="gr_svn627_143"

><td id="143"><a href="#143">143</a></td></tr
><tr id="gr_svn627_144"

><td id="144"><a href="#144">144</a></td></tr
><tr id="gr_svn627_145"

><td id="145"><a href="#145">145</a></td></tr
><tr id="gr_svn627_146"

><td id="146"><a href="#146">146</a></td></tr
><tr id="gr_svn627_147"

><td id="147"><a href="#147">147</a></td></tr
><tr id="gr_svn627_148"

><td id="148"><a href="#148">148</a></td></tr
><tr id="gr_svn627_149"

><td id="149"><a href="#149">149</a></td></tr
><tr id="gr_svn627_150"

><td id="150"><a href="#150">150</a></td></tr
><tr id="gr_svn627_151"

><td id="151"><a href="#151">151</a></td></tr
><tr id="gr_svn627_152"

><td id="152"><a href="#152">152</a></td></tr
><tr id="gr_svn627_153"

><td id="153"><a href="#153">153</a></td></tr
><tr id="gr_svn627_154"

><td id="154"><a href="#154">154</a></td></tr
><tr id="gr_svn627_155"

><td id="155"><a href="#155">155</a></td></tr
><tr id="gr_svn627_156"

><td id="156"><a href="#156">156</a></td></tr
><tr id="gr_svn627_157"

><td id="157"><a href="#157">157</a></td></tr
><tr id="gr_svn627_158"

><td id="158"><a href="#158">158</a></td></tr
><tr id="gr_svn627_159"

><td id="159"><a href="#159">159</a></td></tr
><tr id="gr_svn627_160"

><td id="160"><a href="#160">160</a></td></tr
><tr id="gr_svn627_161"

><td id="161"><a href="#161">161</a></td></tr
><tr id="gr_svn627_162"

><td id="162"><a href="#162">162</a></td></tr
><tr id="gr_svn627_163"

><td id="163"><a href="#163">163</a></td></tr
><tr id="gr_svn627_164"

><td id="164"><a href="#164">164</a></td></tr
><tr id="gr_svn627_165"

><td id="165"><a href="#165">165</a></td></tr
><tr id="gr_svn627_166"

><td id="166"><a href="#166">166</a></td></tr
><tr id="gr_svn627_167"

><td id="167"><a href="#167">167</a></td></tr
><tr id="gr_svn627_168"

><td id="168"><a href="#168">168</a></td></tr
><tr id="gr_svn627_169"

><td id="169"><a href="#169">169</a></td></tr
><tr id="gr_svn627_170"

><td id="170"><a href="#170">170</a></td></tr
><tr id="gr_svn627_171"

><td id="171"><a href="#171">171</a></td></tr
><tr id="gr_svn627_172"

><td id="172"><a href="#172">172</a></td></tr
></table></pre>
<pre><table width="100%"><tr class="nocursor"><td></td></tr></table></pre>
</td>
<td id="lines">
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
<pre class="prettyprint "><table id="src_table_0"><tr
id=sl_svn627_1

><td class="source">// Copyright 2005, Google Inc.<br></td></tr
><tr
id=sl_svn627_2

><td class="source">// All rights reserved.<br></td></tr
><tr
id=sl_svn627_3

><td class="source">//<br></td></tr
><tr
id=sl_svn627_4

><td class="source">// Redistribution and use in source and binary forms, with or without<br></td></tr
><tr
id=sl_svn627_5

><td class="source">// modification, are permitted provided that the following conditions are<br></td></tr
><tr
id=sl_svn627_6

><td class="source">// met:<br></td></tr
><tr
id=sl_svn627_7

><td class="source">//<br></td></tr
><tr
id=sl_svn627_8

><td class="source">//     * Redistributions of source code must retain the above copyright<br></td></tr
><tr
id=sl_svn627_9

><td class="source">// notice, this list of conditions and the following disclaimer.<br></td></tr
><tr
id=sl_svn627_10

><td class="source">//     * Redistributions in binary form must reproduce the above<br></td></tr
><tr
id=sl_svn627_11

><td class="source">// copyright notice, this list of conditions and the following disclaimer<br></td></tr
><tr
id=sl_svn627_12

><td class="source">// in the documentation and/or other materials provided with the<br></td></tr
><tr
id=sl_svn627_13

><td class="source">// distribution.<br></td></tr
><tr
id=sl_svn627_14

><td class="source">//     * Neither the name of Google Inc. nor the names of its<br></td></tr
><tr
id=sl_svn627_15

><td class="source">// contributors may be used to endorse or promote products derived from<br></td></tr
><tr
id=sl_svn627_16

><td class="source">// this software without specific prior written permission.<br></td></tr
><tr
id=sl_svn627_17

><td class="source">//<br></td></tr
><tr
id=sl_svn627_18

><td class="source">// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS<br></td></tr
><tr
id=sl_svn627_19

><td class="source">// &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT<br></td></tr
><tr
id=sl_svn627_20

><td class="source">// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR<br></td></tr
><tr
id=sl_svn627_21

><td class="source">// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT<br></td></tr
><tr
id=sl_svn627_22

><td class="source">// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,<br></td></tr
><tr
id=sl_svn627_23

><td class="source">// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT<br></td></tr
><tr
id=sl_svn627_24

><td class="source">// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,<br></td></tr
><tr
id=sl_svn627_25

><td class="source">// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY<br></td></tr
><tr
id=sl_svn627_26

><td class="source">// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT<br></td></tr
><tr
id=sl_svn627_27

><td class="source">// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE<br></td></tr
><tr
id=sl_svn627_28

><td class="source">// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.<br></td></tr
><tr
id=sl_svn627_29

><td class="source"><br></td></tr
><tr
id=sl_svn627_30

><td class="source">// A sample program demonstrating using Google C++ testing framework.<br></td></tr
><tr
id=sl_svn627_31

><td class="source">//<br></td></tr
><tr
id=sl_svn627_32

><td class="source">// Author: wan@google.com (Zhanyong Wan)<br></td></tr
><tr
id=sl_svn627_33

><td class="source"><br></td></tr
><tr
id=sl_svn627_34

><td class="source">#ifndef GTEST_SAMPLES_SAMPLE3_INL_H_<br></td></tr
><tr
id=sl_svn627_35

><td class="source">#define GTEST_SAMPLES_SAMPLE3_INL_H_<br></td></tr
><tr
id=sl_svn627_36

><td class="source"><br></td></tr
><tr
id=sl_svn627_37

><td class="source">#include &lt;stddef.h&gt;<br></td></tr
><tr
id=sl_svn627_38

><td class="source"><br></td></tr
><tr
id=sl_svn627_39

><td class="source"><br></td></tr
><tr
id=sl_svn627_40

><td class="source">// Queue is a simple queue implemented as a singled-linked list.<br></td></tr
><tr
id=sl_svn627_41

><td class="source">//<br></td></tr
><tr
id=sl_svn627_42

><td class="source">// The element type must support copy constructor.<br></td></tr
><tr
id=sl_svn627_43

><td class="source">template &lt;typename E&gt;  // E is the element type<br></td></tr
><tr
id=sl_svn627_44

><td class="source">class Queue;<br></td></tr
><tr
id=sl_svn627_45

><td class="source"><br></td></tr
><tr
id=sl_svn627_46

><td class="source">// QueueNode is a node in a Queue, which consists of an element of<br></td></tr
><tr
id=sl_svn627_47

><td class="source">// type E and a pointer to the next node.<br></td></tr
><tr
id=sl_svn627_48

><td class="source">template &lt;typename E&gt;  // E is the element type<br></td></tr
><tr
id=sl_svn627_49

><td class="source">class QueueNode {<br></td></tr
><tr
id=sl_svn627_50

><td class="source">  friend class Queue&lt;E&gt;;<br></td></tr
><tr
id=sl_svn627_51

><td class="source"><br></td></tr
><tr
id=sl_svn627_52

><td class="source"> public:<br></td></tr
><tr
id=sl_svn627_53

><td class="source">  // Gets the element in this node.<br></td></tr
><tr
id=sl_svn627_54

><td class="source">  const E&amp; element() const { return element_; }<br></td></tr
><tr
id=sl_svn627_55

><td class="source"><br></td></tr
><tr
id=sl_svn627_56

><td class="source">  // Gets the next node in the queue.<br></td></tr
><tr
id=sl_svn627_57

><td class="source">  QueueNode* next() { return next_; }<br></td></tr
><tr
id=sl_svn627_58

><td class="source">  const QueueNode* next() const { return next_; }<br></td></tr
><tr
id=sl_svn627_59

><td class="source"><br></td></tr
><tr
id=sl_svn627_60

><td class="source"> private:<br></td></tr
><tr
id=sl_svn627_61

><td class="source">  // Creates a node with a given element value.  The next pointer is<br></td></tr
><tr
id=sl_svn627_62

><td class="source">  // set to NULL.<br></td></tr
><tr
id=sl_svn627_63

><td class="source">  explicit QueueNode(const E&amp; an_element) : element_(an_element), next_(NULL) {}<br></td></tr
><tr
id=sl_svn627_64

><td class="source"><br></td></tr
><tr
id=sl_svn627_65

><td class="source">  // We disable the default assignment operator and copy c&#39;tor.<br></td></tr
><tr
id=sl_svn627_66

><td class="source">  const QueueNode&amp; operator = (const QueueNode&amp;);<br></td></tr
><tr
id=sl_svn627_67

><td class="source">  QueueNode(const QueueNode&amp;);<br></td></tr
><tr
id=sl_svn627_68

><td class="source"><br></td></tr
><tr
id=sl_svn627_69

><td class="source">  E element_;<br></td></tr
><tr
id=sl_svn627_70

><td class="source">  QueueNode* next_;<br></td></tr
><tr
id=sl_svn627_71

><td class="source">};<br></td></tr
><tr
id=sl_svn627_72

><td class="source"><br></td></tr
><tr
id=sl_svn627_73

><td class="source">template &lt;typename E&gt;  // E is the element type.<br></td></tr
><tr
id=sl_svn627_74

><td class="source">class Queue {<br></td></tr
><tr
id=sl_svn627_75

><td class="source"> public:<br></td></tr
><tr
id=sl_svn627_76

><td class="source">  // Creates an empty queue.<br></td></tr
><tr
id=sl_svn627_77

><td class="source">  Queue() : head_(NULL), last_(NULL), size_(0) {}<br></td></tr
><tr
id=sl_svn627_78

><td class="source"><br></td></tr
><tr
id=sl_svn627_79

><td class="source">  // D&#39;tor.  Clears the queue.<br></td></tr
><tr
id=sl_svn627_80

><td class="source">  ~Queue() { Clear(); }<br></td></tr
><tr
id=sl_svn627_81

><td class="source"><br></td></tr
><tr
id=sl_svn627_82

><td class="source">  // Clears the queue.<br></td></tr
><tr
id=sl_svn627_83

><td class="source">  void Clear() {<br></td></tr
><tr
id=sl_svn627_84

><td class="source">    if (size_ &gt; 0) {<br></td></tr
><tr
id=sl_svn627_85

><td class="source">      // 1. Deletes every node.<br></td></tr
><tr
id=sl_svn627_86

><td class="source">      QueueNode&lt;E&gt;* node = head_;<br></td></tr
><tr
id=sl_svn627_87

><td class="source">      QueueNode&lt;E&gt;* next = node-&gt;next();<br></td></tr
><tr
id=sl_svn627_88

><td class="source">      for (; ;) {<br></td></tr
><tr
id=sl_svn627_89

><td class="source">        delete node;<br></td></tr
><tr
id=sl_svn627_90

><td class="source">        node = next;<br></td></tr
><tr
id=sl_svn627_91

><td class="source">        if (node == NULL) break;<br></td></tr
><tr
id=sl_svn627_92

><td class="source">        next = node-&gt;next();<br></td></tr
><tr
id=sl_svn627_93

><td class="source">      }<br></td></tr
><tr
id=sl_svn627_94

><td class="source"><br></td></tr
><tr
id=sl_svn627_95

><td class="source">      // 2. Resets the member variables.<br></td></tr
><tr
id=sl_svn627_96

><td class="source">      head_ = last_ = NULL;<br></td></tr
><tr
id=sl_svn627_97

><td class="source">      size_ = 0;<br></td></tr
><tr
id=sl_svn627_98

><td class="source">    }<br></td></tr
><tr
id=sl_svn627_99

><td class="source">  }<br></td></tr
><tr
id=sl_svn627_100

><td class="source"><br></td></tr
><tr
id=sl_svn627_101

><td class="source">  // Gets the number of elements.<br></td></tr
><tr
id=sl_svn627_102

><td class="source">  size_t Size() const { return size_; }<br></td></tr
><tr
id=sl_svn627_103

><td class="source"><br></td></tr
><tr
id=sl_svn627_104

><td class="source">  // Gets the first element of the queue, or NULL if the queue is empty.<br></td></tr
><tr
id=sl_svn627_105

><td class="source">  QueueNode&lt;E&gt;* Head() { return head_; }<br></td></tr
><tr
id=sl_svn627_106

><td class="source">  const QueueNode&lt;E&gt;* Head() const { return head_; }<br></td></tr
><tr
id=sl_svn627_107

><td class="source"><br></td></tr
><tr
id=sl_svn627_108

><td class="source">  // Gets the last element of the queue, or NULL if the queue is empty.<br></td></tr
><tr
id=sl_svn627_109

><td class="source">  QueueNode&lt;E&gt;* Last() { return last_; }<br></td></tr
><tr
id=sl_svn627_110

><td class="source">  const QueueNode&lt;E&gt;* Last() const { return last_; }<br></td></tr
><tr
id=sl_svn627_111

><td class="source"><br></td></tr
><tr
id=sl_svn627_112

><td class="source">  // Adds an element to the end of the queue.  A copy of the element is<br></td></tr
><tr
id=sl_svn627_113

><td class="source">  // created using the copy constructor, and then stored in the queue.<br></td></tr
><tr
id=sl_svn627_114

><td class="source">  // Changes made to the element in the queue doesn&#39;t affect the source<br></td></tr
><tr
id=sl_svn627_115

><td class="source">  // object, and vice versa.<br></td></tr
><tr
id=sl_svn627_116

><td class="source">  void Enqueue(const E&amp; element) {<br></td></tr
><tr
id=sl_svn627_117

><td class="source">    QueueNode&lt;E&gt;* new_node = new QueueNode&lt;E&gt;(element);<br></td></tr
><tr
id=sl_svn627_118

><td class="source"><br></td></tr
><tr
id=sl_svn627_119

><td class="source">    if (size_ == 0) {<br></td></tr
><tr
id=sl_svn627_120

><td class="source">      head_ = last_ = new_node;<br></td></tr
><tr
id=sl_svn627_121

><td class="source">      size_ = 1;<br></td></tr
><tr
id=sl_svn627_122

><td class="source">    } else {<br></td></tr
><tr
id=sl_svn627_123

><td class="source">      last_-&gt;next_ = new_node;<br></td></tr
><tr
id=sl_svn627_124

><td class="source">      last_ = new_node;<br></td></tr
><tr
id=sl_svn627_125

><td class="source">      size_++;<br></td></tr
><tr
id=sl_svn627_126

><td class="source">    }<br></td></tr
><tr
id=sl_svn627_127

><td class="source">  }<br></td></tr
><tr
id=sl_svn627_128

><td class="source"><br></td></tr
><tr
id=sl_svn627_129

><td class="source">  // Removes the head of the queue and returns it.  Returns NULL if<br></td></tr
><tr
id=sl_svn627_130

><td class="source">  // the queue is empty.<br></td></tr
><tr
id=sl_svn627_131

><td class="source">  E* Dequeue() {<br></td></tr
><tr
id=sl_svn627_132

><td class="source">    if (size_ == 0) {<br></td></tr
><tr
id=sl_svn627_133

><td class="source">      return NULL;<br></td></tr
><tr
id=sl_svn627_134

><td class="source">    }<br></td></tr
><tr
id=sl_svn627_135

><td class="source"><br></td></tr
><tr
id=sl_svn627_136

><td class="source">    const QueueNode&lt;E&gt;* const old_head = head_;<br></td></tr
><tr
id=sl_svn627_137

><td class="source">    head_ = head_-&gt;next_;<br></td></tr
><tr
id=sl_svn627_138

><td class="source">    size_--;<br></td></tr
><tr
id=sl_svn627_139

><td class="source">    if (size_ == 0) {<br></td></tr
><tr
id=sl_svn627_140

><td class="source">      last_ = NULL;<br></td></tr
><tr
id=sl_svn627_141

><td class="source">    }<br></td></tr
><tr
id=sl_svn627_142

><td class="source"><br></td></tr
><tr
id=sl_svn627_143

><td class="source">    E* element = new E(old_head-&gt;element());<br></td></tr
><tr
id=sl_svn627_144

><td class="source">    delete old_head;<br></td></tr
><tr
id=sl_svn627_145

><td class="source"><br></td></tr
><tr
id=sl_svn627_146

><td class="source">    return element;<br></td></tr
><tr
id=sl_svn627_147

><td class="source">  }<br></td></tr
><tr
id=sl_svn627_148

><td class="source"><br></td></tr
><tr
id=sl_svn627_149

><td class="source">  // Applies a function/functor on each element of the queue, and<br></td></tr
><tr
id=sl_svn627_150

><td class="source">  // returns the result in a new queue.  The original queue is not<br></td></tr
><tr
id=sl_svn627_151

><td class="source">  // affected.<br></td></tr
><tr
id=sl_svn627_152

><td class="source">  template &lt;typename F&gt;<br></td></tr
><tr
id=sl_svn627_153

><td class="source">  Queue* Map(F function) const {<br></td></tr
><tr
id=sl_svn627_154

><td class="source">    Queue* new_queue = new Queue();<br></td></tr
><tr
id=sl_svn627_155

><td class="source">    for (const QueueNode&lt;E&gt;* node = head_; node != NULL; node = node-&gt;next_) {<br></td></tr
><tr
id=sl_svn627_156

><td class="source">      new_queue-&gt;Enqueue(function(node-&gt;element()));<br></td></tr
><tr
id=sl_svn627_157

><td class="source">    }<br></td></tr
><tr
id=sl_svn627_158

><td class="source"><br></td></tr
><tr
id=sl_svn627_159

><td class="source">    return new_queue;<br></td></tr
><tr
id=sl_svn627_160

><td class="source">  }<br></td></tr
><tr
id=sl_svn627_161

><td class="source"><br></td></tr
><tr
id=sl_svn627_162

><td class="source"> private:<br></td></tr
><tr
id=sl_svn627_163

><td class="source">  QueueNode&lt;E&gt;* head_;  // The first node of the queue.<br></td></tr
><tr
id=sl_svn627_164

><td class="source">  QueueNode&lt;E&gt;* last_;  // The last node of the queue.<br></td></tr
><tr
id=sl_svn627_165

><td class="source">  size_t size_;  // The number of elements in the queue.<br></td></tr
><tr
id=sl_svn627_166

><td class="source"><br></td></tr
><tr
id=sl_svn627_167

><td class="source">  // We disallow copying a queue.<br></td></tr
><tr
id=sl_svn627_168

><td class="source">  Queue(const Queue&amp;);<br></td></tr
><tr
id=sl_svn627_169

><td class="source">  const Queue&amp; operator = (const Queue&amp;);<br></td></tr
><tr
id=sl_svn627_170

><td class="source">};<br></td></tr
><tr
id=sl_svn627_171

><td class="source"><br></td></tr
><tr
id=sl_svn627_172

><td class="source">#endif  // GTEST_SAMPLES_SAMPLE3_INL_H_<br></td></tr
></table></pre>
<pre><table width="100%"><tr class="cursor_stop cursor_hidden"><td></td></tr></table></pre>
</td>
</tr></table>

 
<script type="text/javascript">
 var lineNumUnderMouse = -1;
 
 function gutterOver(num) {
 gutterOut();
 var newTR = document.getElementById('gr_svn627_' + num);
 if (newTR) {
 newTR.className = 'undermouse';
 }
 lineNumUnderMouse = num;
 }
 function gutterOut() {
 if (lineNumUnderMouse != -1) {
 var oldTR = document.getElementById(
 'gr_svn627_' + lineNumUnderMouse);
 if (oldTR) {
 oldTR.className = '';
 }
 lineNumUnderMouse = -1;
 }
 }
 var numsGenState = {table_base_id: 'nums_table_'};
 var srcGenState = {table_base_id: 'src_table_'};
 var alignerRunning = false;
 var startOver = false;
 function setLineNumberHeights() {
 if (alignerRunning) {
 startOver = true;
 return;
 }
 numsGenState.chunk_id = 0;
 numsGenState.table = document.getElementById('nums_table_0');
 numsGenState.row_num = 0;
 if (!numsGenState.table) {
 return; // Silently exit if no file is present.
 }
 srcGenState.chunk_id = 0;
 srcGenState.table = document.getElementById('src_table_0');
 srcGenState.row_num = 0;
 alignerRunning = true;
 continueToSetLineNumberHeights();
 }
 function rowGenerator(genState) {
 if (genState.row_num < genState.table.rows.length) {
 var currentRow = genState.table.rows[genState.row_num];
 genState.row_num++;
 return currentRow;
 }
 var newTable = document.getElementById(
 genState.table_base_id + (genState.chunk_id + 1));
 if (newTable) {
 genState.chunk_id++;
 genState.row_num = 0;
 genState.table = newTable;
 return genState.table.rows[0];
 }
 return null;
 }
 var MAX_ROWS_PER_PASS = 1000;
 function continueToSetLineNumberHeights() {
 var rowsInThisPass = 0;
 var numRow = 1;
 var srcRow = 1;
 while (numRow && srcRow && rowsInThisPass < MAX_ROWS_PER_PASS) {
 numRow = rowGenerator(numsGenState);
 srcRow = rowGenerator(srcGenState);
 rowsInThisPass++;
 if (numRow && srcRow) {
 if (numRow.offsetHeight != srcRow.offsetHeight) {
 numRow.firstChild.style.height = srcRow.offsetHeight + 'px';
 }
 }
 }
 if (rowsInThisPass >= MAX_ROWS_PER_PASS) {
 setTimeout(continueToSetLineNumberHeights, 10);
 } else {
 alignerRunning = false;
 if (startOver) {
 startOver = false;
 setTimeout(setLineNumberHeights, 500);
 }
 }
 }
 function initLineNumberHeights() {
 // Do 2 complete passes, because there can be races
 // between this code and prettify.
 startOver = true;
 setTimeout(setLineNumberHeights, 250);
 window.onresize = setLineNumberHeights;
 }
 initLineNumberHeights();
</script>

 
 
 <div id="log">
 <div style="text-align:right">
 <a class="ifCollapse" href="#" onclick="_toggleMeta(this); return false">Show details</a>
 <a class="ifExpand" href="#" onclick="_toggleMeta(this); return false">Hide details</a>
 </div>
 <div class="ifExpand">
 
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="changelog">
 <p>Change log</p>
 <div>
 <a href="/p/googletest/source/detail?spec=svn627&amp;r=607">r607</a>
 by vladlosev
 on Nov 4, 2011
 &nbsp; <a href="/p/googletest/source/diff?spec=svn627&r=607&amp;format=side&amp;path=/trunk/samples/sample3-inl.h&amp;old_path=/trunk/samples/sample3-inl.h&amp;old=383">Diff</a>
 </div>
 <pre>Improves conformance to the Google C++
Style Guide (by Greg Miller).</pre>
 </div>
 
 
 
 
 
 
 <script type="text/javascript">
 var detail_url = '/p/googletest/source/detail?r=607&spec=svn627';
 var publish_url = '/p/googletest/source/detail?r=607&spec=svn627#publish';
 // describe the paths of this revision in javascript.
 var changed_paths = [];
 var changed_urls = [];
 
 changed_paths.push('/trunk/include/gtest/gtest-spi.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/gtest-spi.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/gtest-test-part.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/gtest-test-part.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/gtest.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/gtest.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/gtest_pred_impl.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/gtest_pred_impl.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-port.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-port.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-string.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-string.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-tuple.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-tuple.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-tuple.h.pump');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-tuple.h.pump?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-type-util.h');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-type-util.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/include/gtest/internal/gtest-type-util.h.pump');
 changed_urls.push('/p/googletest/source/browse/trunk/include/gtest/internal/gtest-type-util.h.pump?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/samples/sample10_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample10_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/samples/sample1_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample1_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/samples/sample2.h');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample2.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/samples/sample2_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample2_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/samples/sample3-inl.h');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample3-inl.h?r\x3d607\x26spec\x3dsvn627');
 
 var selected_path = '/trunk/samples/sample3-inl.h';
 
 
 changed_paths.push('/trunk/samples/sample5_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/samples/sample5_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/scripts/gen_gtest_pred_impl.py');
 changed_urls.push('/p/googletest/source/browse/trunk/scripts/gen_gtest_pred_impl.py?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/src/gtest-death-test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/src/gtest-death-test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/src/gtest-internal-inl.h');
 changed_urls.push('/p/googletest/source/browse/trunk/src/gtest-internal-inl.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/src/gtest-port.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/src/gtest-port.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/src/gtest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/src/gtest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/src/gtest_main.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/src/gtest_main.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-death-test_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-death-test_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-linked_ptr_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-linked_ptr_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-listener_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-listener_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-param-test_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-param-test_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-param-test_test.h');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-param-test_test.h?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-port_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-port_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest-printers_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest-printers_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_environment_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_environment_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_no_test_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_no_test_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_output_test_.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_output_test_.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_pred_impl_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_pred_impl_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_repeat_test.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_repeat_test.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 changed_paths.push('/trunk/test/gtest_unittest.cc');
 changed_urls.push('/p/googletest/source/browse/trunk/test/gtest_unittest.cc?r\x3d607\x26spec\x3dsvn627');
 
 
 function getCurrentPageIndex() {
 for (var i = 0; i < changed_paths.length; i++) {
 if (selected_path == changed_paths[i]) {
 return i;
 }
 }
 }
 function getNextPage() {
 var i = getCurrentPageIndex();
 if (i < changed_paths.length - 1) {
 return changed_urls[i + 1];
 }
 return null;
 }
 function getPreviousPage() {
 var i = getCurrentPageIndex();
 if (i > 0) {
 return changed_urls[i - 1];
 }
 return null;
 }
 function gotoNextPage() {
 var page = getNextPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoPreviousPage() {
 var page = getPreviousPage();
 if (!page) {
 page = detail_url;
 }
 window.location = page;
 }
 function gotoDetailPage() {
 window.location = detail_url;
 }
 function gotoPublishPage() {
 window.location = publish_url;
 }
</script>

 
 <style type="text/css">
 #review_nav {
 border-top: 3px solid white;
 padding-top: 6px;
 margin-top: 1em;
 }
 #review_nav td {
 vertical-align: middle;
 }
 #review_nav select {
 margin: .5em 0;
 }
 </style>
 <div id="review_nav">
 <table><tr><td>Go to:&nbsp;</td><td>
 <select name="files_in_rev" onchange="window.location=this.value">
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/gtest-spi.h?r=607&amp;spec=svn627"
 
 >/trunk/include/gtest/gtest-spi.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/gtest-test-part.h?r=607&amp;spec=svn627"
 
 >.../include/gtest/gtest-test-part.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/gtest.h?r=607&amp;spec=svn627"
 
 >/trunk/include/gtest/gtest.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/gtest_pred_impl.h?r=607&amp;spec=svn627"
 
 >.../include/gtest/gtest_pred_impl.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-port.h?r=607&amp;spec=svn627"
 
 >...lude/gtest/internal/gtest-port.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-string.h?r=607&amp;spec=svn627"
 
 >...de/gtest/internal/gtest-string.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-tuple.h?r=607&amp;spec=svn627"
 
 >...ude/gtest/internal/gtest-tuple.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-tuple.h.pump?r=607&amp;spec=svn627"
 
 >...test/internal/gtest-tuple.h.pump</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-type-util.h?r=607&amp;spec=svn627"
 
 >...gtest/internal/gtest-type-util.h</option>
 
 <option value="/p/googletest/source/browse/trunk/include/gtest/internal/gtest-type-util.h.pump?r=607&amp;spec=svn627"
 
 >.../internal/gtest-type-util.h.pump</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample10_unittest.cc?r=607&amp;spec=svn627"
 
 >/trunk/samples/sample10_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample1_unittest.cc?r=607&amp;spec=svn627"
 
 >/trunk/samples/sample1_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample2.h?r=607&amp;spec=svn627"
 
 >/trunk/samples/sample2.h</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample2_unittest.cc?r=607&amp;spec=svn627"
 
 >/trunk/samples/sample2_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample3-inl.h?r=607&amp;spec=svn627"
 selected="selected"
 >/trunk/samples/sample3-inl.h</option>
 
 <option value="/p/googletest/source/browse/trunk/samples/sample5_unittest.cc?r=607&amp;spec=svn627"
 
 >/trunk/samples/sample5_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/scripts/gen_gtest_pred_impl.py?r=607&amp;spec=svn627"
 
 >...k/scripts/gen_gtest_pred_impl.py</option>
 
 <option value="/p/googletest/source/browse/trunk/src/gtest-death-test.cc?r=607&amp;spec=svn627"
 
 >/trunk/src/gtest-death-test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/src/gtest-internal-inl.h?r=607&amp;spec=svn627"
 
 >/trunk/src/gtest-internal-inl.h</option>
 
 <option value="/p/googletest/source/browse/trunk/src/gtest-port.cc?r=607&amp;spec=svn627"
 
 >/trunk/src/gtest-port.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/src/gtest.cc?r=607&amp;spec=svn627"
 
 >/trunk/src/gtest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/src/gtest_main.cc?r=607&amp;spec=svn627"
 
 >/trunk/src/gtest_main.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-death-test_test.cc?r=607&amp;spec=svn627"
 
 >...nk/test/gtest-death-test_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-linked_ptr_test.cc?r=607&amp;spec=svn627"
 
 >...nk/test/gtest-linked_ptr_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-listener_test.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest-listener_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-param-test_test.cc?r=607&amp;spec=svn627"
 
 >...nk/test/gtest-param-test_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-param-test_test.h?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest-param-test_test.h</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-port_test.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest-port_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest-printers_test.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest-printers_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_environment_test.cc?r=607&amp;spec=svn627"
 
 >...k/test/gtest_environment_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_no_test_unittest.cc?r=607&amp;spec=svn627"
 
 >...k/test/gtest_no_test_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_output_test_.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest_output_test_.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_pred_impl_unittest.cc?r=607&amp;spec=svn627"
 
 >...test/gtest_pred_impl_unittest.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_repeat_test.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest_repeat_test.cc</option>
 
 <option value="/p/googletest/source/browse/trunk/test/gtest_unittest.cc?r=607&amp;spec=svn627"
 
 >/trunk/test/gtest_unittest.cc</option>
 
 </select>
 </td></tr></table>
 
 
 



 <div style="white-space:nowrap">
 
 <a href="https://www.google.com/accounts/ServiceLogin?service=code&amp;ltmpl=phosting&amp;continue=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogletest%2Fsource%2Fbrowse%2Ftrunk%2Fsamples%2Fsample3-inl.h&amp;followup=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogletest%2Fsource%2Fbrowse%2Ftrunk%2Fsamples%2Fsample3-inl.h"
 >Sign in</a> to write a code review</div>


 
 </div>
 
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="older_bubble">
 <p>Older revisions</p>
 
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/googletest/source/detail?spec=svn627&r=383">r383</a>
 by vladlosev
 on Feb 27, 2010
 &nbsp; <a href="/p/googletest/source/diff?spec=svn627&r=383&amp;format=side&amp;path=/trunk/samples/sample3-inl.h&amp;old_path=/trunk/samples/sample3-inl.h&amp;old=40">Diff</a>
 <br>
 <pre class="ifOpened">Makes all samples compile with -Wall
-Wshadow -Werror.</pre>
 </div>
 
 <div class="closed" style="margin-bottom:3px;" >
 <img class="ifClosed" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/plus.gif" >
 <img class="ifOpened" onclick="_toggleHidden(this)" src="http://www.gstatic.com/codesite/ph/images/minus.gif" >
 <a href="/p/googletest/source/detail?spec=svn627&r=40">r40</a>
 by shiqian
 on Jul 3, 2008
 &nbsp; <a href="/p/googletest/source/diff?spec=svn627&r=40&amp;format=side&amp;path=/trunk/samples/sample3-inl.h&amp;old_path=/trunk/samples/sample3-inl.h&amp;old=">Diff</a>
 <br>
 <pre class="ifOpened">Initial import.
</pre>
 </div>
 
 
 <a href="/p/googletest/source/list?path=/trunk/samples/sample3-inl.h&start=607">All revisions of this file</a>
 </div>
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 
 <div class="pmeta_bubble_bg" style="border:1px solid white">
 <div class="round4"></div>
 <div class="round2"></div>
 <div class="round1"></div>
 <div class="box-inner">
 <div id="fileinfo_bubble">
 <p>File info</p>
 
 <div>Size: 5365 bytes,
 172 lines</div>
 
 <div><a href="//googletest.googlecode.com/svn/trunk/samples/sample3-inl.h">View raw file</a></div>
 </div>
 
 </div>
 <div class="round1"></div>
 <div class="round2"></div>
 <div class="round4"></div>
 </div>
 </div>
 </div>


</div>

</div>
</div>

<script src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/prettify/prettify.js"></script>
<script type="text/javascript">prettyPrint();</script>


<script src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/source_file_scripts.js"></script>

 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/kibbles.js"></script>
 <script type="text/javascript">
 var lastStop = null;
 var initialized = false;
 
 function updateCursor(next, prev) {
 if (prev && prev.element) {
 prev.element.className = 'cursor_stop cursor_hidden';
 }
 if (next && next.element) {
 next.element.className = 'cursor_stop cursor';
 lastStop = next.index;
 }
 }
 
 function pubRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftRevealed(data) {
 updateCursorForCell(data.cellId, 'cursor_stop cursor_hidden');
 if (initialized) {
 reloadCursors();
 }
 }
 
 function draftDestroyed(data) {
 updateCursorForCell(data.cellId, 'nocursor');
 if (initialized) {
 reloadCursors();
 }
 }
 function reloadCursors() {
 kibbles.skipper.reset();
 loadCursors();
 if (lastStop != null) {
 kibbles.skipper.setCurrentStop(lastStop);
 }
 }
 // possibly the simplest way to insert any newly added comments
 // is to update the class of the corresponding cursor row,
 // then refresh the entire list of rows.
 function updateCursorForCell(cellId, className) {
 var cell = document.getElementById(cellId);
 // we have to go two rows back to find the cursor location
 var row = getPreviousElement(cell.parentNode);
 row.className = className;
 }
 // returns the previous element, ignores text nodes.
 function getPreviousElement(e) {
 var element = e.previousSibling;
 if (element.nodeType == 3) {
 element = element.previousSibling;
 }
 if (element && element.tagName) {
 return element;
 }
 }
 function loadCursors() {
 // register our elements with skipper
 var elements = CR_getElements('*', 'cursor_stop');
 var len = elements.length;
 for (var i = 0; i < len; i++) {
 var element = elements[i]; 
 element.className = 'cursor_stop cursor_hidden';
 kibbles.skipper.append(element);
 }
 }
 function toggleComments() {
 CR_toggleCommentDisplay();
 reloadCursors();
 }
 function keysOnLoadHandler() {
 // setup skipper
 kibbles.skipper.addStopListener(
 kibbles.skipper.LISTENER_TYPE.PRE, updateCursor);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_top', 50);
 // Set the 'offset' option to return the middle of the client area
 // an option can be a static value, or a callback
 kibbles.skipper.setOption('padding_bottom', 100);
 // Register our keys
 kibbles.skipper.addFwdKey("n");
 kibbles.skipper.addRevKey("p");
 kibbles.keys.addKeyPressListener(
 'u', function() { window.location = detail_url; });
 kibbles.keys.addKeyPressListener(
 'r', function() { window.location = detail_url + '#publish'; });
 
 kibbles.keys.addKeyPressListener('j', gotoNextPage);
 kibbles.keys.addKeyPressListener('k', gotoPreviousPage);
 
 
 }
 </script>
<script src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/code_review_scripts.js"></script>
<script type="text/javascript">
 function showPublishInstructions() {
 var element = document.getElementById('review_instr');
 if (element) {
 element.className = 'opened';
 }
 }
 var codereviews;
 function revsOnLoadHandler() {
 // register our source container with the commenting code
 var paths = {'svn627': '/trunk/samples/sample3-inl.h'}
 codereviews = CR_controller.setup(
 {"profileUrl":null,"token":null,"assetHostPath":"http://www.gstatic.com/codesite/ph","domainName":null,"assetVersionPath":"http://www.gstatic.com/codesite/ph/17790938420062995905","projectHomeUrl":"/p/googletest","relativeBaseUrl":"","projectName":"googletest","loggedInUserEmail":null}, '', 'svn627', paths,
 CR_BrowseIntegrationFactory);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, showPublishInstructions);
 
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_PUB_PLATE, pubRevealed);
 codereviews.registerActivityListener(CR_ActivityType.REVEAL_DRAFT_PLATE, draftRevealed);
 codereviews.registerActivityListener(CR_ActivityType.DISCARD_DRAFT_COMMENT, draftDestroyed);
 
 
 
 
 
 
 
 var initialized = true;
 reloadCursors();
 }
 window.onload = function() {keysOnLoadHandler(); revsOnLoadHandler();};

</script>
<script type="text/javascript" src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/dit_scripts.js"></script>

 
 
 
 <script type="text/javascript" src="http://www.gstatic.com/codesite/ph/17790938420062995905/js/ph_core.js"></script>
 
 
 
 
</div> 

<div id="footer" dir="ltr">
 <div class="text">
 <a href="/projecthosting/terms.html">Terms</a> -
 <a href="http://www.google.com/privacy.html">Privacy</a> -
 <a href="/p/support/">Project Hosting Help</a>
 </div>
</div>
 <div class="hostedBy" style="margin-top: -20px;">
 <span style="vertical-align: top;">Powered by <a href="http://code.google.com/projecthosting/">Google Project Hosting</a></span>
 </div>

 
 


 
 </body>
</html>

