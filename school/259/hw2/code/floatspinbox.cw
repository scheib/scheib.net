<!DOCTYPE CW><CW>
<customwidgets>
    <customwidget>
        <class>FloatSpinBox</class>
        <header location="local">floatspinbox.h</header>
        <sizehint>
            <width>-1</width>
            <height>-1</height>
        </sizehint>
        <container>0</container>
        <sizepolicy>
            <hordata>5</hordata>
            <verdata>5</verdata>
        </sizepolicy>
        <pixmap>
            <data format="XPM.GZ" length="2350">789c8d946d53143910c7dff329b6c83beaaa9dc93c645257be101411441651c1bdba179924232c222a200f57f7ddafe7dfd9d95d843ad210f24bfa9f7477323c5b1b1d8d77476bcf562e2edde5891ff963f773b416aecece6efffafbf93f2babba18f18fd123bdfac7ca2a4d467ea43234f08719e70efc119c677965c06f136b63c161c68dec371d3882bf808bacb405f81c5c66c68afe0c6cb3e8a0570e1cf3bcacb07e92b8761eebb1e73ccf9b2660fd1558e74523f15e246e9dc4fb135ceaccd7e01fe09a1d84653fab0b9b8337c12e0f35cea3efc29aa7c0888f8fab4303be046bed9cc4b30b2e745149fe8760c726febf7ae665db4a3dee12bb944f0546037f05dbd2fb16ecc1be2a82d4e7a0e7322bbd95fa176034f031d854dacafd96e05035a9fe7be058354ef63bedb92aebcaa23eaa03575551897e1d5c57e93ee85dcfb5a98d93fa6f839d89adac2b706b6c2bf1e99e4d5e77b5e4f34dd8d651f2cfc068e00d70639ab4df27b035ce087f06c7dec039b833c148bdaf7a6ef2a60a12ff3eb86cb4e9c02db871b997fd8ec0a1691ba907f2b7655b77a8a722b0b155aa770346c33abe07db32e2fe14eecb39573b9caf709eeb5c7052ff71cfbef6ba957a1830b720fc62c611f7b18ff716ca9079c9ef7d62ed25ff6bb00945cae716ecf8394bbe35b80b21487db77a8e3a6601f7a7705fb1e01979ef37e026d651f2b5e0187d94f85f268e9decf7bae78eaf57ea456fc09e4df2d901a3493e7323458edac599fbb6ac607f4f81e25315ecdfd11756043a7e8a825af63f817fa0299d3e49f135f9f776f65836330547f46df09ee2f791c84401fff3e43bb707231b14274bbe62df1f8a4cbe7ffab1e0b778ce0391c97f58aee9cca66cb3f1394d1f8deaf461fbff3b7f8aa5332e96ec92aed87ecd63a26bba61bb1df2b8bb57a317b44e1bf4925ed16652bca62d56bca1eba4d84eaf496c9d76e82ded72ff8ef6e0bfc5e331ed73ff7e88ea60a1a61bbcf2813e72ff89c650dcf0f8908eb8ff4ce3e195dc0d77d12b263cdaa18cf24131e1bf981914f3c81615fa37855e78bb7b29b23e8f824aee2bd254a73c0aae176696bea883748aa186f7b53451c45eac516a36b3ac60cd66af508e0ad5727526ca53ad02cf1fcd67ee29b65564cd1e1daa8eb4ea78f7c05ebd669879ec95a8a0fc6cb43cb3faef9f2bff0138925d07</data>
        </pixmap>
        <signal>valueChanged(double)</signal>
        <signal>valueChanged(const QString&amp;)</signal>
        <signal>destroyed()</signal>
        <slot access="public">setPrefix(const QString&amp;)</slot>
        <slot access="public">setSuffix(const QString&amp;)</slot>
        <slot access="public">stepDown()</slot>
        <slot access="public">setDoubleMin(double)</slot>
        <slot access="public">setDoubleMax(double)</slot>
        <slot access="public">setDoubleRange(double,double)</slot>
        <slot access="public">setDoubleLineStep(double)</slot>
        <slot access="public">setEnabled( bool )</slot>
        <slot access="public">setDisabled( bool )</slot>
        <slot access="public">setCaption( const QString &amp; )</slot>
        <slot access="public">setIcon( const QPixmap &amp; )</slot>
        <slot access="public">setIconText( const QString &amp; )</slot>
        <slot access="public">setMouseTracking( bool enable )</slot>
        <slot access="public">setFocus()</slot>
        <slot access="public">clearFocus()</slot>
        <slot access="public">setUpdatesEnabled( bool enable )</slot>
        <slot access="public">update()</slot>
        <slot access="public">update( int , int, int, int )</slot>
        <slot access="public">update( const QRect &amp; )</slot>
        <slot access="public">repaint()</slot>
        <slot access="public">repaint( bool )</slot>
        <slot access="public">repaint( int, int, int, int, bool )</slot>
        <slot access="public">repaint( const QRect &amp;, bool )</slot>
        <slot access="public">repaint( const QRegion &amp;, bool )</slot>
        <slot access="public">show()</slot>
        <slot access="public">hide()</slot>
        <slot access="public">showMinimized()</slot>
        <slot access="public">showMaximized()</slot>
        <slot access="public">showFullScreen()</slot>
        <slot access="public">showNormal()</slot>
        <slot access="public">polish()</slot>
        <slot access="public">constPolish()</slot>
        <slot access="public">close()</slot>
        <slot access="public">raise()</slot>
        <slot access="public">lower()</slot>
        <slot access="public">stackUnder( QWidget * )</slot>
        <slot access="public">move( int,int )</slot>
        <slot access="public">move( const QPoint &amp; )</slot>
        <slot access="public">resize( int , int )</slot>
        <slot access="public">resize( const QSize &amp; )</slot>
        <slot access="public">setGeometry( int , int , int, int )</slot>
        <slot access="public">setGeometry( const QRect &amp; )</slot>
        <property type="String">text</property>
        <property type="String">prefix</property>
        <property type="String">suffix</property>
        <property type="String">cleanText</property>
        <property type="String">specialValueText</property>
        <property type="Bool">wrapping</property>
        <property type="ButtonSymbols">buttonSymbols</property>
        <property type="double">doubleMaxValue</property>
        <property type="double">doubleMinValue</property>
        <property type="double">doubleLineStep</property>
        <property type="double">doubleValue</property>
        <property type="String">maxValueStr</property>
        <property type="String">minValueStr</property>
        <property type="String">lineStepStr</property>
        <property type="String">valueStr</property>
        <property type="Int">frameWidth</property>
        <property type="QRect">contentsRect</property>
        <property type="Shape">frameShape</property>
        <property type="Shadow">frameShadow</property>
        <property type="Int">lineWidth</property>
        <property type="Int">margin</property>
        <property type="Int">midLineWidth</property>
        <property type="Bool">isTopLevel</property>
        <property type="Bool">isModal</property>
        <property type="Bool">isPopup</property>
        <property type="Bool">isDesktop</property>
        <property type="Bool">enabled</property>
        <property type="QRect">geometry</property>
        <property type="QRect">frameGeometry</property>
        <property type="int">x</property>
        <property type="int">y</property>
        <property type="QPoint">pos</property>
        <property type="QSize">frameSize</property>
        <property type="QSize">size</property>
        <property type="int">width</property>
        <property type="int">height</property>
        <property type="QRect">rect</property>
        <property type="QRect">childrenRect</property>
        <property type="QRegion">childrenRegion</property>
        <property type="QSizePolicy">sizePolicy</property>
        <property type="QSize">minimumSize</property>
        <property type="QSize">maximumSize</property>
        <property type="int">minimumWidth</property>
        <property type="int">minimumHeight</property>
        <property type="int">maximumWidth</property>
        <property type="int">maximumHeight</property>
        <property type="QSize">sizeIncrement</property>
        <property type="QSize">baseSize</property>
        <property type="BackgroundMode">backgroundMode</property>
        <property type="QColor">backgroundColor</property>
        <property type="QColor">foregroundColor</property>
        <property type="QPixmap">backgroundPixmap</property>
        <property type="QColorGroup">colorGroup</property>
        <property type="QPalette">palette</property>
        <property type="Bool">ownPalette</property>
        <property type="QFont">font</property>
        <property type="Bool">ownFont</property>
        <property type="QCursor">cursor</property>
        <property type="Bool">ownCursor</property>
        <property type="QString">caption</property>
        <property type="QPixmap">icon</property>
        <property type="QString">iconText</property>
        <property type="Bool">mouseTracking</property>
        <property type="Bool">isActiveWindow</property>
        <property type="Bool">focusEnabled</property>
        <property type="FocusPolicy">focusPolicy</property>
        <property type="Bool">focus</property>
        <property type="Bool">updatesEnabled</property>
        <property type="Bool">visible</property>
        <property type="QRect">visibleRect</property>
        <property type="Bool">hidden</property>
        <property type="Bool">minimized</property>
        <property type="QSize">sizeHint</property>
        <property type="QSize">minimumSizeHint</property>
        <property type="QRect">microFocusHint</property>
        <property type="Bool">acceptDrops</property>
        <property type="Bool">autoMask</property>
        <property type="BackgroundOrigin">backgroundOrigin</property>
        <property type="Bool">customWhatsThis</property>
        <property type="QCString">name</property>
    </customwidget>
</customwidgets>
</CW>
