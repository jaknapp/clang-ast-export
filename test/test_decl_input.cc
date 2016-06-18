namespace SpaceOfName {
   template <typename ClassTemplateParam1, typename ClassTemplateParam2>
   class ClassType {
      public:
      void MemberFunc();
      int _member;
   };

   template<typename ClassTemplateParam1, typename ClassTemplateParam2>
   void ClassType<ClassTemplateParam1, ClassTemplateParam2>::MemberFunc() {
   }
   void c_func() {
   }
};