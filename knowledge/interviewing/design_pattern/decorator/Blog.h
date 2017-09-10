#ifndef BLOG_H_
#define BLOG_H_
#include <stdio.h>

class Blog {
public:
        Blog() {}
        virtual ~Blog() {}
public:
        virtual void Show() = 0;
};

class CsdnBlog: public Blog {
public:
        CsdnBlog() {}
        ~CsdnBlog() {}
public:
        void Show()
        {
                printf("csdn blog: "); 
        }
};

class SinaBlog: public Blog {
public:
        SinaBlog() {}
        ~SinaBlog() {}
public:
        void Show()
        {
                printf("sina blog: "); 
        }
};

class BlogDecorator: public Blog {
public:
        BlogDecorator(Blog *pblog):m_Blog(pblog) {}
        virtual ~BlogDecorator() {}
protected:
        Blog *m_Blog;
};

class BriefStyle: public BlogDecorator {
public:
        BriefStyle(Blog *pblog):BlogDecorator(pblog) {}
        virtual ~BriefStyle() {}
public:
        void Show() { m_Blog->Show(); printf("brief style;"); }
};

class BrightStyle: public BlogDecorator {
public:
        BrightStyle(Blog *pblog):BlogDecorator(pblog) {}
        virtual ~BrightStyle() {}
public:
        void Show() { m_Blog->Show(); printf("bright style;"); }
};

class DarkStyle: public BlogDecorator {
public:
        DarkStyle(Blog *pblog):BlogDecorator(pblog) {}
        virtual ~DarkStyle() {}
public:
        void Show() { m_Blog->Show(); printf("dark style;"); }
};

class WithGrass: public BlogDecorator {
public:
        WithGrass(Blog *pblog):BlogDecorator(pblog) {}
        virtual ~WithGrass() {}
public:
        void Show() { m_Blog->Show(); printf("with grass;"); }
};
#endif  //BLOG_H_
